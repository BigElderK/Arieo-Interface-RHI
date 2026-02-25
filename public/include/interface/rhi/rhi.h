#pragma once
#include "interface/window/window.h"
#include "interface/rhi/rhi_enums.h"
namespace Arieo::Interface::RHI
{
    class IRenderDevice;

    class IFence
    {
    public:
        virtual void wait() = 0;
        virtual void reset() = 0;
    };

    class ISemaphore
    {
    public:
    };

    class IRenderSurface
    {
    public:
        virtual Base::Interface<Interface::Window::IWindow> getAttachedWindow() = 0;
    };

    class IRenderInstance
    {
    public:
        virtual std::vector<std::string>& getHardwareInfomations() = 0;
        virtual Base::Interface<IRenderSurface> createSurface(Base::Interface<Interface::Window::IWindow> window) = 0;
        virtual void destroySurface(Base::Interface<IRenderSurface> surface) = 0;

        virtual Base::Interface<IRenderDevice> createDevice(size_t hardware_index, Base::Interface<IRenderSurface> surface) = 0;
        virtual void destroyDevice(Base::Interface<IRenderDevice> device) = 0;
    };

    class IFramebuffer
    {

    };

    class IBuffer
    {
    public:
        virtual void* mapMemory(size_t offset, size_t size) = 0;
        virtual void unmapMemory() = 0;
    };

    class IPipeline
    {

    };

    class IImageView
    {

    };

    class IImageSampler
    {

    };

    class ISwapchain
    {
    public:
        virtual Base::Math::Rect<size_t>& getExtent() = 0;
        virtual std::vector<Base::Interface<IImageView>>& getImageViews() = 0;
        virtual std::uint32_t acquireNextImageIndex(Base::Interface<ISemaphore>) = 0;
        virtual bool isLost() = 0;
    };

    class IImage
    {
    public:
        virtual size_t getMemorySize() = 0;
        virtual Base::Interface<IImageView> getImageView() = 0;
        virtual Base::Interface<IImageSampler> getImageSampler() = 0;
    };

    class IShader
    {

    };

    class IDescriptorSet
    {
    public:
        virtual void bindBuffer(size_t bind_index, Base::Interface<IBuffer>, size_t offset, size_t size) = 0;
        virtual void bindImage(size_t bind_index, Base::Interface<IImage>) = 0;
    };

    class IDescriptorPool
    {
    public:
        virtual Base::Interface<IDescriptorSet> allocateDescriptorSet(Base::Interface<IPipeline> pipeline) = 0;
        virtual void freeDescriptorSet(Base::Interface<IDescriptorSet>) = 0;
    };

        class ICommandBuffer
    {
    public:
        virtual void reset() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void beginRenderPass(Base::Interface<IPipeline>, Base::Interface<IFramebuffer>) = 0;
        virtual void endRenderPass() = 0;

        virtual void bindVertexBuffer(Base::Interface<IBuffer>, uint32_t offset) = 0;
        virtual void bindIndexBuffer(Base::Interface<IBuffer>, uint32_t offset) = 0;

        virtual void bindPipeline(Base::Interface<IPipeline>) = 0;

        virtual void draw(std::uint32_t vertex_count, std::uint32_t instance_count, std::uint32_t first_vertex, std::uint32_t first_instance) = 0;
        virtual void drawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;

        virtual void bindDescriptorSets(Base::Interface<IPipeline>, Base::Interface<IDescriptorSet>) = 0;

        virtual void copyBuffer(Base::Interface<IBuffer>, Base::Interface<IBuffer>, std::uint32_t) = 0;
        virtual void copyBufferToImage(Base::Interface<IBuffer>, Base::Interface<IImage>) = 0;
        virtual void prepareDepthImage(Base::Interface<IImage> depth_image) = 0;
    };

    class ICommandPool
    {
    public:
        virtual Base::Interface<ICommandBuffer> allocateCommandBuffer() = 0;
        virtual void freeCommandBuffer(Base::Interface<ICommandBuffer>) = 0;
    };

    class ICommandQueue
    {
    public:
        virtual Base::Interface<ICommandPool> createCommandPool() = 0;
        virtual void destroyCommandPool(Base::Interface<ICommandPool>) = 0;
        virtual void waitIdle() = 0;
    };

    class IRenderCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void submitCommand(Base::Interface<ICommandBuffer>, Base::Interface<IFence>, Base::Interface<ISemaphore> wait_semaphore, Base::Interface<ISemaphore> signal_semaphore) = 0;
        virtual void submitCommand(Base::Interface<ICommandBuffer>) = 0;
    };

    class IPresentCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void present(Base::Interface<ISwapchain>, std::uint32_t swapchain_image_index, Base::Interface<IFramebuffer>, Base::Interface<ISemaphore> signal_semaphore) = 0;
    };

    class IRenderDevice
    {
    public:
        virtual Format findSupportedFormat(const std::vector<Format>& candidate_formats, ImageTiling, FormatFeatureFlags) = 0;

        virtual Base::Interface<IRenderCommandQueue> getGraphicsCommandQueue() = 0;
        virtual Base::Interface<IPresentCommandQueue> getPresentCommandQueue() = 0;

        virtual Base::Interface<ISwapchain> createSwapchain(Base::Interface<IRenderSurface>) = 0;
        virtual void destroySwapchain(Base::Interface<ISwapchain>) = 0;

        virtual Base::Interface<IImage> createImage(std::uint32_t width, std::uint32_t height, Format format, ImageAspectFlags aspect, ImageTiling tiling, ImageUsageFlags usage, MemoryUsage memory_usage) = 0;
        virtual void destroyImage(Base::Interface<IImage>) = 0;

        virtual Base::Interface<IFramebuffer> createFramebuffer(Base::Interface<IPipeline>, Base::Interface<ISwapchain>, std::vector<Base::Interface<IImageView>>& attachment_array) = 0;
        virtual void destroyFramebuffer(Base::Interface<IFramebuffer>) = 0;

        virtual Base::Interface<IShader> createShader(void* buf, size_t buf_size) = 0;
        virtual void destroyShader(Base::Interface<IShader>) = 0; 

        //TODO: remove target_image_view from here
        virtual Base::Interface<IPipeline> createPipeline(Base::Interface<IShader> vert_shader, Base::Interface<IShader> frag_shader, Base::Interface<IImageView> target_color_attachment, Base::Interface<IImageView> target_dept_attachment) = 0;
        virtual void destroyPipeline(Base::Interface<IPipeline>) = 0;

        virtual Base::Interface<IFence> createFence() = 0;
        virtual void destroyFence(Base::Interface<IFence>) = 0;

        virtual Base::Interface<ISemaphore> createSemaphore() = 0;
        virtual void destroySemaphore(Base::Interface<ISemaphore>) = 0;

        virtual Base::Interface<IBuffer> createBuffer(size_t size, BufferUsageBitFlags buffer_usage, BufferAllocationFlags allocation_flag, MemoryUsage memory_usage) = 0;
        virtual void destroyBuffer(Base::Interface<IBuffer>) = 0;

        virtual Base::Interface<IDescriptorPool> createDescriptorPool(size_t capacity) = 0;
        virtual void destroyDescriptorPool(Base::Interface<IDescriptorPool>) = 0;

        virtual void waitIdle() = 0;
    };
}