//
// EPITECH PROJECT, 2018
// arcade
// File description:
// lib opening hpp
//

#ifndef OPENLIB_HPP_
	#define OPENLIB_HPP_
	#include <dlfcn.h>
	#include <string>
	#include <stdexcept>

	template <class T>
	class DynamicLib {
		public:
			DynamicLib(const std::string &libName)
				: _libName(libName), _libObject(nullptr) {}
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
					throw std::runtime_error(err);
			}
			void instantiate()
			{
				std::string err = "Missing \'create_object\'";

				err += "symbol in \'";
				err += _libName;
				err += "\'!";
				if (!dlsym(_handle, "create_object"))
					throw std::runtime_error(err);
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

#endif /* !OPENLIB_HPP_ */
