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
		DynamicLib(const std::string &libName)
			: _libName(libName) {}
		~DynamicLib() {dlclose(_handle);}
		void open()
		{
			std::string name = "./";
			std::string err = "Cannot open \'";

			name += _libName;
			err += _libName;
			err += "\' library!";
			_handle = dlopen(_libName.c_str(), RTLD_LAZY);
			if (!_handle)
				throw Exception(err, "DynamicLib");
		}
		void instantiate()
		{
			std::string err = "Missing \'create_object\'";

			err += "symbol in \'";
			err += _libName;
			err += "\'!";
			if (!dlsym(_handle, "create_object"))
				throw Exception(err, "DynamicLib");
			T *(*create)() = (T *(*)()) dlsym(_handle,
						"create_object");
			_libObject = create();
		}
		T *getObject() { return _libObject; }
	private:
		std::string _libName;
		void *_handle;
		T *_libObject;
	};
}

#endif /* !DYNAMICLIB_HPP_ */
