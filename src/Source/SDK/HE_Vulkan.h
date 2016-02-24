#pragma once

#include <vulkan\vulkan.h>

#include <string>
#include <vector>
#include <exception>
#include <string_span.h>

namespace vk
{
	/// Instance
	/*
		VkInstanceCreateInfo MakeInstanceCreateInfo(const VkApplicationInfo* pApplicationInfo, 
			gsl::span<char const* const> enabledLayerNames = {}, 
			gsl::span<char const* const>enabledExtensionNames = {},
			const void* pNext = nullptr);

		Makes a valid instance of the VkInstanceCreateInfo structure

		� pApplicationInfo is NULL or a pointer to an instance of VkApplicationInfo. If not NULL, this information
		helps implementations recognize behavior inherent to classes of applications. VkApplicationInfo is defined in
		detail below.
		� enabledLayerNames is an array of null-terminated UTF-8 strings containing
		the names of layers to enable.
		� enabledExtensionNames is an array of null-terminated UTF-8 strings
		containing the names of extensions to enable.
		� pNext is NULL or a pointer to an extension-specific structure.

		Valid Usage:
		� If pApplicationInfo is not NULL, pApplicationInfo must be a pointer to a valid VkApplicationInfo
		structure
		� Any given element of enabledLayerNames must be the name of a layer present on the system, exactly
		matching a string returned in the VkLayerProperties structure by
		vkEnumerateInstanceLayerProperties
		� Any given element of enabledExtensionNames must be the name of an extension present on the system,
		exactly matching a string returned in the VkExtensionProperties structure by
		vkEnumerateInstanceExtensionProperties
		� If an extension listed in enabledExtensionNames is provided as part of a layer, then both the layer and
		extension must be enabled to enable that extension
	*/
	VkInstanceCreateInfo MakeInstanceCreateInfo(VkApplicationInfo const* pApplicationInfo,
		gsl::span<gsl::czstring<> const> pEnabledLayerNames = {},
		gsl::span<gsl::czstring<> const> pEnabledExtensionNames = {},
		const void* pNext = nullptr) noexcept;

	/*
		VkApplicationInfo MakeApplicationInfo(char const* pApplicationName, uint32_t applicationVersion, const void* pNext = nullptr);

		Makes a valid instance of the VkApplicationInfo structure

		� pApplicationName is a pointer to a null-terminated UTF-8 string containing the name of the application.
		� applicationVersion is an unsigned integer variable containing the developer-supplied version number of the
		application.
		� For the engine name, the engine version and the API version, the function assumes "HazelEngine" with the proper version
		and uses VK_API_VERSION
		� pNext is NULL or a pointer to an extension-specific structure.

		Valid Usage:
		� If pApplicationName is not NULL, pApplicationName must be a null-terminated string
	*/
	VkApplicationInfo MakeApplicationInfo(gsl::czstring<> pApplicationName, uint32_t applicationVersion, const void* pNext = nullptr) noexcept;
	
	/*
		VkInstance CreateInstance(VkInstanceCreateInfo const& createInfo, VkAllocationCallbacks const* pAllocator = nullptr);

		Creates an instance of the Vulkan library, and initializes the module. Also allows the application to pass
		information about itself to the implementation

		� createInfo refers to an instance of VkInstanceCreateInfo controlling creation of the instance.
		� pAllocator controls host memory allocation
		� returns a VkInstance handle in which the resulting instance is returned.

		Valid Usage:
		� createInfo must refer to a valid VkInstanceCreateInfo structure
		� If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure

		Failure
		� VK_ERROR_OUT_OF_HOST_MEMORY
		� VK_ERROR_OUT_OF_DEVICE_MEMORY
		� VK_ERROR_INITIALIZATION_FAILED
		� VK_ERROR_LAYER_NOT_PRESENT
		� VK_ERROR_EXTENSION_NOT_PRESENT
		� VK_ERROR_INCOMPATIBLE_DRIVER
	*/
	VkInstance CreateInstance(VkInstanceCreateInfo const& createInfo, VkAllocationCallbacks const* pAllocator = nullptr);

	/*
		void DestroyInstance(VkInstance instance, VkAllocationCallbacks const* pAllocator = nullptr);

		Must be called on a VkInstance after all its child objects have been destroyed before the program termination

		� instance is the handle of the instance to destroy.
		� pAllocator controls host memory allocation

		Valid Usage
		� If instance is not NULL, instance must be a valid VkInstance handle
		� If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure
		� All child objects created using instance must have been destroyed prior to destroying instance
		� If VkAllocationCallbacks were provided when instance was created, a compatible set of callbacks must
		be provided here
		� If no VkAllocationCallbacks were provided when instance was created, pAllocator must be NULL
		� The deallocation function provided in the vkAllocationCallbacks must have a no-throw guarantee

		Host Synchronization
		� Host access to instance must be externally synchronized
	*/
	void DestroyInstance(VkInstance instance, VkAllocationCallbacks const* pAllocator = nullptr) noexcept;

	/// Physical Devices
	/*
		std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(VkInstance instance);

		Retrieves a list of physical device objects representing the physical devices installed in the system

		� instance is a handle to a Vulkan instance previously created with CreateInstance.

		Valid Usage
		� instance must be a valid VkInstance handle

		Failure
		� VK_ERROR_OUT_OF_HOST_MEMORY
		� VK_ERROR_OUT_OF_DEVICE_MEMORY
		� VK_ERROR_INITIALIZATION_FAILED
	*/
	std::vector<VkPhysicalDevice> EnumeratePhysicalDevices(VkInstance instance);

	/*
		VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept;

		Queries the general properties of the physical device

		� physicalDevice is the handle to the physical device whose properties will be queried.

		Valid Usage
		� physicalDevice must be a valid VkPhysicalDevice handle
	*/
	VkPhysicalDeviceProperties GetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice) noexcept;

	/*
		VkQueueFamilyProperties GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice) noexcept;

		Queries the properties of queues available on a physical device

		� physicalDevice is the handle to the physical device whose properties will be queried.

		Valid Usage
		� physicalDevice must be a valid VkPhysicalDevice handle
	*/
	std::vector<VkQueueFamilyProperties> GetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice) noexcept;

	/// Devices
	/*
		VkDeviceCreateInfo MakeDeviceCreateInfo(gsl::span<const VkDeviceQueueCreateInfo> queueCreateInfos,
			gsl::span<char const* const> enabledLayerNames,
			gsl::span<char const* const> enabledExtensionNames,
			VkPhysicalDeviceFeatures const& enabledFeatures,
			const void* pNext = nullptr
			);

		Makes a valid instance of the VkDeviceCreateInfo structure

		� QueueCreateInfos is an array of VkDeviceQueueCreateInfo structures describing the queues
		that are requested to be created along with the logical device.
		� enabledLayerNames is a  an array of null-terminated UTF-8 strings containing
		the names of layers to enable for the created device. 
		� enabledExtensionNames is an array of null-terminated UTF-8 strings
		containing the names of extensions to enable for the created device.
		� enabledFeatures refers to a VkPhysicalDeviceFeatures structure that contains boolean indicators of
		all the features to be enabled.

		Valid Usage
		� queueCreateInfos must be an array of valid
		VkDeviceQueueCreateInfo structures
		� enabledFeatures must refer to a valid VkPhysicalDeviceFeatures structure
		� The size of queueCreateInfos must be greater than 0
		� Any given element of enabledLayerNames must be the name of a layer present on the system, exactly
		matching a string returned in the VkLayerProperties structure by
		EnumerateDeviceLayerProperties
		� Any given element of enabledExtensionNames must be the name of an extension present on the system,
		exactly matching a string returned in the VkExtensionProperties structure by
		EnumerateDeviceExtensionProperties
		� If an extension listed in enabledExtensionNames is provided as part of a layer, then both the layer and
		extension must be enabled to enable that extension
		� The queueFamilyIndex member of any given element of queueCreateInfos must be unique within
		queueCreateInfos
	*/
	VkDeviceCreateInfo MakeDeviceCreateInfo(gsl::span<const VkDeviceQueueCreateInfo> queueCreateInfos,
		gsl::span<gsl::czstring<> const> enabledLayerNames,
		gsl::span<gsl::czstring<> const> enabledExtensionNames,
		VkPhysicalDeviceFeatures const& enabledFeatures,
		const void* pNext = nullptr
		) noexcept;

	/*
		VkPhysicalDevice CreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo& createInfo, const VkAllocationCallbacks* pAllocator = nullptr);

		Creates a logical device as a connection to a physical device

		� physicalDevice must be one of the device handles returned from a call to EnumeratePhysicalDevices
		� createInfo refers to a VkDeviceCreateInfo structure containing information about how to create the
		device.

		Valid Usage
		� physicalDevice must be a valid VkPhysicalDevice handle
		� pCreateInfo must refer to a valid VkDeviceCreateInfo structure
		� If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure

		Failure
		� VK_ERROR_OUT_OF_HOST_MEMORY
		� VK_ERROR_OUT_OF_DEVICE_MEMORY
		� VK_ERROR_INITIALIZATION_FAILED
		� VK_ERROR_LAYER_NOT_PRESENT
		� VK_ERROR_EXTENSION_NOT_PRESENT
		� VK_ERROR_FEATURE_NOT_PRESENT
		� VK_ERROR_TOO_MANY_OBJECTS
		� VK_ERROR_DEVICE_LOST
	*/
	VkDevice CreateDevice(VkPhysicalDevice physicalDevice, VkDeviceCreateInfo const& createInfo, const VkAllocationCallbacks* pAllocator = nullptr);

	/*
		void DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator) noexcept;

		Must be called on a VkDevice after all its child objects have been destroyed before the program termination

		� device is the logical device to destroy.
		� pAllocator controls host memory allocation

		Valid Usage
		� If device is not NULL, device must be a valid VkDevice handle
		� If pAllocator is not NULL, pAllocator must be a pointer to a valid VkAllocationCallbacks structure
		� All child objects created on device must have been destroyed prior to destroying device
		� If VkAllocationCallbacks were provided when device was created, a compatible set of callbacks must be
		provided here
		� If no VkAllocationCallbacks were provided when device was created, pAllocator must be NULL

		Host Synchronization
		� Host access to device must be externally synchronized
	*/
	void DestroyDevice(VkDevice device, const VkAllocationCallbacks* pAllocator = nullptr) noexcept;

	/*
		void DeviceWaitIdle(VkDevice device);
		void DeviceWaitIdle(VkDevice device, std::nothrow_t) noexcept;

		Waits until all the device's queues are idle

		� device is the logical device to idle
		� If using the std::nothrow_t version, the function will silently fail on errors. Useful if Waiting before destroying
		the Device, as you might be destroying the Device as part of a destructor while an exception is already being thrown

		Valid Usage
		� device must be a valid VkDevice handle

		Host Synchronization
		� Host access to all VkQueue objects created from device must be externally synchronized

		Failure
		� VK_ERROR_OUT_OF_HOST_MEMORY
		� VK_ERROR_OUT_OF_DEVICE_MEMORY
		� VK_ERROR_DEVICE_LOST
	*/
	void DeviceWaitIdle(VkDevice device);
	void DeviceWaitIdle(VkDevice device, std::nothrow_t) noexcept;

	/// Queues
	/*
		VkDeviceQueueCreateInfo MakeDeviceQueueCreateInfo(uint32_t queueFamilyIndex, gsl::span<float const> queuePriorities, void const* pNext = nullptr);

		Makes a valid instance of the VkDeviceQueueCreateInfo structure

		� queueFamilyIndex is an unsigned integer indicating the index of the queue family to create on this device. The
		value of this index corresponds to the index of an element of the array that was returned
		by GetPhysicalDeviceQueueFamilyProperties.
		� queuePriorities is an array of normalized floating point values, both specifying the number of queues to be
		created and specifying priorities of work that will be submitted to each created queue.
		� pNext is NULL or a pointer to an extension-specific structure.

		Valid Usage
		� The size of queuePriorities must be greater than 0
		� queueFamilyIndex must be less than the number of elements returned by
		GetPhysicalDeviceQueueFamilyProperties
		� The size of queuePriorities must be less than or equal to the value of the queueCount member of the
		VkQueueFamilyProperties structure, as returned in the "queueFamilyIndex"th element of GetPhysicalDeviceQueueFamilyProperties
		� The value of any given element of pQueuePriorities must be between 0.0 and 1.0 inclusive
	*/
	VkDeviceQueueCreateInfo MakeDeviceQueueCreateInfo(uint32_t queueFamilyIndex, gsl::span<float const> queuePriorities, void const* pNext = nullptr) noexcept;

	/*
		VkQueue GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex) noexcept;

		Retrieves a handle to a VkQueue object

		� device is the logical device that owns the queue.
		� queueFamilyIndex is the index of the queue family to which the queue belongs.
		� queueIndex is the index within this queue family of the queue to retrieve.

		Valid Usage
		� device must be a valid VkDevice handle
		� queueFamilyIndex must be one of the queue family indexes specified when device was created, via the
		VkDeviceQueueCreateInfo structure
		� queueIndex must be less than the number of queues created for the specified queue family index when device
		was created, via the queueCount member of the VkDeviceQueueCreateInfo structure
	*/
	VkQueue GetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex) noexcept;

	/*
		void QueueWaitIdle(VkQueue queue);
		void QueueWaitIdle(VkQueue queue, std::nothrow_t);

		Waits on the completion of all work within the queue

		� queue is the queue on which to wait.

		Valid Usage
		� queue must be a valid VkQueue handle

		Command Properties
			Supported Queue Types: Any

		Failure
		� VK_ERROR_OUT_OF_HOST_MEMORY
		� VK_ERROR_OUT_OF_DEVICE_MEMORY
		� VK_ERROR_DEVICE_LOST
	*/
	void QueueWaitIdle(VkQueue queue);
	void QueueWaitIdle(VkQueue queue, std::nothrow_t) noexcept;

	///Features
	/*
		VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice) noexcept;

		Queries the supported features of the physical device. See the VkPhysicalDeviceFeatures structure

		� physicalDevice is the physical device from which to query the supported features.

		Valid Usage
		� physicalDevice must be a valid VkPhysicalDevice handle
	*/
	VkPhysicalDeviceFeatures GetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice) noexcept;

	namespace PhysicalDeviceType
	{
		gsl::cstring_span<> String(VkPhysicalDeviceType e);
	}

	class ResultErrorException : public std::exception
	{
	public:
		ResultErrorException(VkResult e);
		ResultErrorException(VkResult e, gsl::cstring_span<> sContext);

		virtual const char* what() const override;

	private:
		std::string m_sMessage;
	};
}

std::string to_string(VkPhysicalDeviceType e);