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
        virtual Base::Interop<Interface::Window::IWindow> getAttachedWindow() = 0;
    };

    class IRenderInstance
    {
    public:
        virtual std::vector<std::string>& getHardwareInfomations() = 0;
        virtual Base::Interop<IRenderSurface> createSurface(Base::Interop<Interface::Window::IWindowManager> window_manager, Base::Interop<Interface::Window::IWindow> window) = 0;
        virtual void destroySurface(Base::Interop<IRenderSurface> surface) = 0;

        virtual Base::Interop<IRenderDevice> createDevice(size_t hardware_index, Base::Interop<IRenderSurface> surface) = 0;
        virtual void destroyDevice(Base::Interop<IRenderDevice> device) = 0;
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
        virtual std::vector<Base::Interop<IImageView>>& getImageViews() = 0;
        virtual std::uint32_t acquireNextImageIndex(Base::Interop<ISemaphore>) = 0;
        virtual bool isLost() = 0;
    };

    class IImage
    {
    public:
        virtual size_t getMemorySize() = 0;
        virtual Base::Interop<IImageView> getImageView() = 0;
        virtual Base::Interop<IImageSampler> getImageSampler() = 0;
    };

    class IShader
    {

    };

    class IDescriptorSet
    {
    public:
        virtual void bindBuffer(size_t bind_index, Base::Interop<IBuffer>, size_t offset, size_t size) = 0;
        virtual void bindImage(size_t bind_index, Base::Interop<IImage>) = 0;
    };

    class IDescriptorPool
    {
    public:
        virtual Base::Interop<IDescriptorSet> allocateDescriptorSet(Base::Interop<IPipeline> pipeline) = 0;
        virtual void freeDescriptorSet(Base::Interop<IDescriptorSet>) = 0;
    };

        class ICommandBuffer
    {
    public:
        virtual void reset() = 0;

        virtual void begin() = 0;
        virtual void end() = 0;

        virtual void beginRenderPass(Base::Interop<IPipeline>, Base::Interop<IFramebuffer>) = 0;
        virtual void endRenderPass() = 0;

        virtual void bindVertexBuffer(Base::Interop<IBuffer>, uint32_t offset) = 0;
        virtual void bindIndexBuffer(Base::Interop<IBuffer>, uint32_t offset) = 0;

        virtual void bindPipeline(Base::Interop<IPipeline>) = 0;

        virtual void draw(std::uint32_t vertex_count, std::uint32_t instance_count, std::uint32_t first_vertex, std::uint32_t first_instance) = 0;
        virtual void drawIndexed(uint32_t index_count, uint32_t instance_count, uint32_t first_index, int32_t vertex_offset, uint32_t first_instance) = 0;

        virtual void bindDescriptorSets(Base::Interop<IPipeline>, Base::Interop<IDescriptorSet>) = 0;

        virtual void copyBuffer(Base::Interop<IBuffer>, Base::Interop<IBuffer>, std::uint32_t) = 0;
        virtual void copyBufferToImage(Base::Interop<IBuffer>, Base::Interop<IImage>) = 0;
        virtual void prepareDepthImage(Base::Interop<IImage> depth_image) = 0;
    };

    class ICommandPool
    {
    public:
        virtual Base::Interop<ICommandBuffer> allocateCommandBuffer() = 0;
        virtual void freeCommandBuffer(Base::Interop<ICommandBuffer>) = 0;
    };

    class ICommandQueue
    {
    public:
        virtual Base::Interop<ICommandPool> createCommandPool() = 0;
        virtual void destroyCommandPool(Base::Interop<ICommandPool>) = 0;
        virtual void waitIdle() = 0;
    };

    class IRenderCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void submitCommand(Base::Interop<ICommandBuffer>, Base::Interop<IFence>, Base::Interop<ISemaphore> wait_semaphore, Base::Interop<ISemaphore> signal_semaphore) = 0;
        virtual void submitCommand(Base::Interop<ICommandBuffer>) = 0;
    };

    class IPresentCommandQueue
        : public ICommandQueue
    {
    public:
        virtual void present(Base::Interop<ISwapchain>, std::uint32_t swapchain_image_index, Base::Interop<IFramebuffer>, Base::Interop<ISemaphore> signal_semaphore) = 0;
    };

    class IRenderDevice
    {
    public:
        virtual Format findSupportedFormat(const std::vector<Format>& candidate_formats, ImageTiling, FormatFeatureFlags) = 0;

        virtual Base::Interop<IRenderCommandQueue> getGraphicsCommandQueue() = 0;
        virtual Base::Interop<IPresentCommandQueue> getPresentCommandQueue() = 0;

        virtual Base::Interop<ISwapchain> createSwapchain(Base::Interop<IRenderSurface>) = 0;
        virtual void destroySwapchain(Base::Interop<ISwapchain>) = 0;

        virtual Base::Interop<IImage> createImage(std::uint32_t width, std::uint32_t height, Format format, ImageAspectFlags aspect, ImageTiling tiling, ImageUsageFlags usage, MemoryUsage memory_usage) = 0;
        virtual void destroyImage(Base::Interop<IImage>) = 0;

        virtual Base::Interop<IFramebuffer> createFramebuffer(Base::Interop<IPipeline>, Base::Interop<ISwapchain>, std::vector<Base::Interop<IImageView>>& attachment_array) = 0;
        virtual void destroyFramebuffer(Base::Interop<IFramebuffer>) = 0;

        virtual Base::Interop<IShader> createShader(void* buf, size_t buf_size) = 0;
        virtual void destroyShader(Base::Interop<IShader>) = 0; 

        //TODO: remove target_image_view from here
        virtual Base::Interop<IPipeline> createPipeline(Base::Interop<IShader> vert_shader, Base::Interop<IShader> frag_shader, Base::Interop<IImageView> target_color_attachment, Base::Interop<IImageView> target_dept_attachment) = 0;
        virtual void destroyPipeline(Base::Interop<IPipeline>) = 0;

        virtual Base::Interop<IFence> createFence() = 0;
        virtual void destroyFence(Base::Interop<IFence>) = 0;

        virtual Base::Interop<ISemaphore> createSemaphore() = 0;
        virtual void destroySemaphore(Base::Interop<ISemaphore>) = 0;

        virtual Base::Interop<IBuffer> createBuffer(size_t size, BufferUsageBitFlags buffer_usage, BufferAllocationFlags allocation_flag, MemoryUsage memory_usage) = 0;
        virtual void destroyBuffer(Base::Interop<IBuffer>) = 0;

        virtual Base::Interop<IDescriptorPool> createDescriptorPool(size_t capacity) = 0;
        virtual void destroyDescriptorPool(Base::Interop<IDescriptorPool>) = 0;

        virtual void waitIdle() = 0;
    };
}