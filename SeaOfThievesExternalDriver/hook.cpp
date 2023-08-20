#include "hook.h"


bool nullhook::call_kernel_function(void* kernel_function_address)
{
	if (!kernel_function_address)
		return false;

	DbgPrintEx(0, 0, "Entry call_kernel_func\n");

	PVOID* function = reinterpret_cast<PVOID*>(get_system_module_export("\\SystemRoot\\System32\\drivers\\dxgkrnl.sys",
																		"NtOpenCompositionSurfaceSectionInfo"));
	DbgPrintEx(0, 0, "Function: 0x%p\n", function);

	if (!function)
		return false;

	BYTE orig[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

	BYTE shell_code[] = { 0x48, 0xB8 }; // mov rax, xxx
	BYTE shell_code_end[] = { 0xFF, 0xE0 }; //jmp rax


	RtlSecureZeroMemory(&orig, sizeof(orig));
	memcpy((PVOID)((ULONG_PTR)orig), &shell_code, sizeof(shell_code));
	uintptr_t hook_address = reinterpret_cast<uintptr_t>(kernel_function_address);
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code)), &hook_address, sizeof(void*));
	memcpy((PVOID)((ULONG_PTR)orig + sizeof(shell_code) + sizeof(void*)), &shell_code_end, sizeof(shell_code_end));

	DbgPrintEx(0, 0, "Writing to NT func \n");
	write_to_read_only_memory(function, &orig, sizeof(orig));
	DbgPrintEx(0, 0, "Done \n");
	return true;
}

NTSTATUS nullhook::hook_handler(PVOID called_param)
{

	DbgPrintEx(0, 0, "Hook Handler\n");

	NULL_MEMORY* instructions = (NULL_MEMORY*)called_param;

	if (instructions->req_base != FALSE)
	{

		ANSI_STRING AS;
		UNICODE_STRING ModuleName;

		RtlInitAnsiString(&AS, instructions->module_name);
		RtlAnsiStringToUnicodeString(&ModuleName, &AS, TRUE);

		PEPROCESS process;
		PsLookupProcessByProcessId((HANDLE)instructions->pid, &process);
		ULONG64 base_address64 = NULL;
		base_address64 = get_module_base_x64(process, ModuleName);
		instructions->base_address = base_address64;
		RtlFreeUnicodeString(&ModuleName);
	}

	if (instructions->write != FALSE)
	{
		if (instructions->address < 0x7FFFFFFFFFFF && instructions->address > 0)
		{

			PVOID kernelBuff = ExAllocatePool(NonPagedPool, instructions->size);

			if (!kernelBuff)
			{
				DbgPrintEx(0, 0, "NOTKERNELBUFF %p\n", kernelBuff);
				return STATUS_UNSUCCESSFUL;
			}

			if (!memcpy(kernelBuff, instructions->buffer_address, instructions->size))
			{
				DbgPrintEx(0, 0, "NOTMEMCOPY\n");
				return STATUS_UNSUCCESSFUL;
			}

			PEPROCESS process;
			PsLookupProcessByProcessId((HANDLE)instructions->pid, &process);
			write_kernel_memory((HANDLE)instructions->pid, instructions->address, kernelBuff, instructions->size);
			ExFreePool(kernelBuff);

		}
	}

	if (instructions->read != FALSE)
	{
		if (instructions->address < 0x7FFFFFFFFFFF && instructions->address > 0)
		{
			read_kernel_memory((HANDLE)instructions->pid, instructions->address, instructions->output, instructions->size);
		}
	}

	return STATUS_SUCCESS;
}
