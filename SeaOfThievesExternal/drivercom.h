
#pragma once

#ifndef DRIVERCOM_H
#define DRIVERCOM_H

#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <memory>
#include <string_view>
#include <cstdint>
#include <vector>


#include "handledisposer.h"
#include "nullmemory.h"

class Driver {

public:

	static std::uint32_t process_id;
	static std::uintptr_t base_address;

	template<typename ... Arg>
	static uint64_t call_hook(const Arg ... args);

	using unique_handle = std::unique_ptr<HANDLE, HandleDisposer>;

	static std::uint32_t get_process_id(std::string_view process_name);

	static ULONG64 get_module_base_address(const char* module_name);

	template <class T>
	static T read(UINT_PTR read_address)
	{
		T response{};
		NULL_MEMORY instructions;
		instructions.pid = process_id;
		instructions.size = sizeof(T);
		instructions.address = read_address;
		instructions.read = TRUE;
		instructions.write = FALSE;
		instructions.req_base = FALSE;
		instructions.output = &response;
		Driver::call_hook(&instructions);

		return response;
	}
	
	template<typename S>
	static bool write(UINT_PTR write_address, const S& value)
	{
		return Driver::write_memory(write_address, (UINT_PTR)&value, sizeof(S));
	}

	static bool write_memory(UINT_PTR write_address, UINT_PTR source_address, SIZE_T write_size);

	

};

#endif // !DRIVERCOM_H
