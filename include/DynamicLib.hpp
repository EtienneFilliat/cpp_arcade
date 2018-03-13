//
// EPITECH PROJECT, 2018
// arcade
// File description:
// lib opening hpp
//

#ifndef DYNAMICLIB_HPP_
	#define DYNAMICLIB_HPP_
	#include <dlfcn.h>
	#include <string>
	#include "Exception.hpp"

namespace arc {

	template <class T>
	class DynamicLib {
	public:
		typedef T *(*fptr) ();
		//using fptr = T *(*)();
		DynamicLib(const std::string &libName)
			: _libName(libName) {}
		~DynamicLib() { dlclose(_handle); }
		void open()
		{
			std::string name = "./";
			std::string err = "Cannot open \'";

			name += _libName;
			err += _libName;
			err += "\' library!";
			_handle = dlopen(name.c_str(), RTLD_LAZY);
			if (!_handle)
				throw Exception(err, "DynamicLib");
		}
		fptr instantiate()
		{
			std::string err = "Missing \'create_object\'";

			err += "symbol in \'";
			err += _libName;
			err += "\'!";
			if (!dlsym(_handle, "create_object"))
				throw Exception(err, "DynamicLib");
			fptr create = (fptr) dlsym(_handle,
						"create_object");
			return create;
		}
		void *getHandle()
		{
			return _handle;
		}
	private:
		std::string _libName;
		void *_handle;
	};
}

#endif /* !DYNAMICLIB_HPP_ */
