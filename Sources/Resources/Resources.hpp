#pragma once

#include <memory>
#include <vector>
#include "Engine/Engine.hpp"
#include "Maths/Timer.hpp"
#include "IResource.hpp"

namespace acid
{
	/// <summary>
	/// A module used for managing resources.
	/// </summary>
	class ACID_EXPORT Resources :
		public IModule
	{
	private:
		std::vector<std::shared_ptr<IResource>> m_resources;
		Timer m_timerPurge;
	public:
		/// <summary>
		/// Gets this engine instance.
		/// </summary>
		/// <returns> The current module instance. </returns>
		static Resources *Get()
		{
			return Engine::Get()->GetModule<Resources>();
		}

		/// <summary>
		/// Creates a new Resources module.
		/// </summary>
		Resources();

		/// <summary>
		/// Deconstructor for the Resources module.
		/// </summary>
		~Resources();

		void Update() override;

		std::shared_ptr<IResource> Get(const std::string &filename);

		void Add(std::shared_ptr<IResource> resource);

		bool Remove(std::shared_ptr<IResource> resource);

		bool Remove(const std::string &filename);
	};
}
