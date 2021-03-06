#include "MeshAnimated.hpp"

#include "Files/Xml/FileXml.hpp"
#include "Helpers/FileSystem.hpp"

namespace acid
{
	const Matrix4 MeshAnimated::CORRECTION = Matrix4(Matrix4::IDENTITY.Rotate(Maths::Radians(-90.0f), Vector3::RIGHT));
	const int MeshAnimated::MAX_JOINTS = 50;
	const int MeshAnimated::MAX_WEIGHTS = 3;

	MeshAnimated::MeshAnimated(const std::string &filename) :
		Mesh(),
		m_filename(Files::SearchFile(filename)),
		m_model(nullptr),
		m_headJoint(nullptr),
		m_animator(nullptr),
		m_animation(nullptr)
	{
		TrySetModel(m_filename);
	}

	MeshAnimated::~MeshAnimated()
	{
		delete m_headJoint;
		delete m_animation;
		delete m_animator;
	}

	void MeshAnimated::Update()
	{
		if (m_animator != nullptr)
		{
			m_animator->Update();
		}

		if (m_headJoint != nullptr)
		{
			m_jointMatrices.clear();
			m_jointMatrices.resize(MAX_JOINTS);
			AddJointsToArray(*m_headJoint, m_jointMatrices);
			//	m_jointMatrices.shrink_to_fit();
		}
	}

	void MeshAnimated::Load(LoadedValue *value)
	{
		TrySetModel(value->GetChild("Model")->GetString());
	}

	void MeshAnimated::Write(LoadedValue *destination)
	{
		destination->GetChild("Model", true)->SetString(m_filename);
	}

	void MeshAnimated::TrySetModel(const std::string &filename)
	{
		delete m_animation;
		delete m_headJoint;
		delete m_animator;

		if (!FileSystem::FileExists(filename))
		{
			fprintf(stderr, "Animation file does not exist: '%s'\n", m_filename.c_str());
			return;
		}

		FileXml file = FileXml(filename);
		file.Load();

		SkinLoader skinLoader = SkinLoader(file.GetParent()->GetChild("COLLADA")->GetChild("library_controllers"), MAX_WEIGHTS);
		SkeletonLoader skeletonLoader = SkeletonLoader(file.GetParent()->GetChild("COLLADA")->GetChild("library_visual_scenes"), skinLoader.GetJointOrder());
		GeometryLoader geometryLoader = GeometryLoader(file.GetParent()->GetChild("COLLADA")->GetChild("library_geometries"), skinLoader.GetVerticesSkinData());

		auto vertices = geometryLoader.GetVertices();
		auto indices = geometryLoader.GetIndices();
		m_model = std::make_shared<Model>(vertices, indices, filename);
		m_headJoint = CreateJoints(skeletonLoader.GetHeadJoint());
		m_headJoint->CalculateInverseBindTransform(Matrix4());
		m_animator = new Animator(m_headJoint);

		AnimationLoader animationLoader = AnimationLoader(file.GetParent()->GetChild("COLLADA")->GetChild("library_animations"),
			file.GetParent()->GetChild("COLLADA")->GetChild("library_visual_scenes"));
		m_animation = new Animation(animationLoader.GetLengthSeconds(), animationLoader.GetKeyframeData());
		m_animator->DoAnimation(m_animation);
	}

	Joint *MeshAnimated::CreateJoints(JointData *data)
	{
		Joint *j = new Joint(data->GetIndex(), data->GetNameId(), data->GetBindLocalTransform());

		for (auto &child : data->GetChildren())
		{
			j->AddChild(CreateJoints(child));
		}

		return j;
	}

	void MeshAnimated::AddJointsToArray(const Joint &headJoint, std::vector<Matrix4> &jointMatrices)
	{
		if (headJoint.GetIndex() < jointMatrices.size())
		{
			jointMatrices[headJoint.GetIndex()] = headJoint.GetAnimatedTransform();
		}

		for (auto &childJoint : headJoint.GetChildren())
		{
			AddJointsToArray(*childJoint, jointMatrices);
		}
	}
}
