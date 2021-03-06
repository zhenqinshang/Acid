#pragma once

#include <memory>
#include "Renderer/Commands/CommandBuffer.hpp"
#include "ShaderProgram.hpp"

namespace acid
{
	class ACID_EXPORT IPipeline
	{
	public:
		IPipeline()
		{
		}

		virtual ~IPipeline()
		{
		}

		void BindPipeline(const CommandBuffer &commandBuffer) const
		{
		//	vkCmdPushConstants(commandBuffer.GetCommandBuffer(), GetPipelineLayout(), VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(pushConstants), pushConstants.data());
			vkCmdBindPipeline(commandBuffer.GetCommandBuffer(), GetPipelineBindPoint(), GetPipeline());
		}

		virtual std::shared_ptr<ShaderProgram> GetShaderProgram() const = 0;

		virtual VkDescriptorSetLayout GetDescriptorSetLayout() const = 0;

		virtual VkDescriptorPool GetDescriptorPool() const = 0;

		virtual VkPipeline GetPipeline() const = 0;

		virtual VkPipelineLayout GetPipelineLayout() const = 0;

		virtual VkPipelineBindPoint GetPipelineBindPoint() const = 0;
	};
}
