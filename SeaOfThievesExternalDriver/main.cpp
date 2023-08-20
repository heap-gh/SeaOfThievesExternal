#include "hook.h"

extern "C" void Unload(PDRIVER_OBJECT driver_object) {

	UNREFERENCED_PARAMETER(driver_object);
	DbgPrintEx(0, 0, "Unloaded Driver\n");
}

extern "C" NTSTATUS DriverEntry(PDRIVER_OBJECT driver_object, PUNICODE_STRING reg_path)
{
	UNREFERENCED_PARAMETER(driver_object);
	UNREFERENCED_PARAMETER(reg_path);

	driver_object->DriverUnload = Unload;
	nullhook::call_kernel_function(&nullhook::hook_handler);

	return STATUS_SUCCESS;
}
