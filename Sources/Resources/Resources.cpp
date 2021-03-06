#include "Resources.hpp"

#include <algorithm>

namespace acid
{
	Resources::Resources() :
		m_resources(std::vector<std::shared_ptr<IResource>>()),
		m_timerPurge(Timer(5.0f))
	{
	}

	Resources::~Resources()
	{
	}

	void Resources::Update()
	{
		if (m_timerPurge.IsPassedTime())
		{
			m_timerPurge.ResetStartTime();

			for (auto it = m_resources.begin(); it != m_resources.end();)
			{
				if ((*it).use_count() <= 1)
				{
					fprintf(stdout, "Resource '%s' erased\n", (*it)->GetFilename().c_str());
					it = m_resources.erase(it);
					continue;
				}

				++it;
			}
		}
	}

	std::shared_ptr<IResource> Resources::Get(const std::string &filename)
	{
		for (auto &resource : m_resources)
		{
			if (resource != nullptr && resource->GetFilename() == filename)
			{
				return resource;
			}
		}

		return nullptr;
	}

	void Resources::Add(std::shared_ptr<IResource> resource)
	{
		if (std::find(m_resources.begin(), m_resources.end(), resource) != m_resources.end())
		{
			return;
		}

		m_resources.emplace_back(resource);
	}

	bool Resources::Remove(std::shared_ptr<IResource> resource)
	{
		for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
		{
			if (*it == resource)
			{
				m_resources.erase(it);
				return true;
			}
		}

		return false;
	}

	bool Resources::Remove(const std::string &filename)
	{
		for (auto it = m_resources.begin(); it != m_resources.end(); ++it)
		{
			if ((*it)->GetFilename() == filename)
			{
				m_resources.erase(it);
				return true;
			}
		}

		return false;
	}
}
