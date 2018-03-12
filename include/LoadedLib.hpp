//
// EPITECH PROJECT, 2018
// arcade
// File description:
// game lib manager hpp
//


#ifndef LOADEDLIB_HPP_
	#define LOADEDLIB_HPP_
	#include <string>
	#include <memory>

namespace arc {

	template <class T>
	class LoadedLib {
	public:
		LoadedLib(T *libObject)
			: _object(libObject) {}
		~LoadedLib() {}
		std::unique_ptr<T> &run() { return _object; }

	private:
		std::unique_ptr<T> _object;
	};
}

#endif /* !LOADEDLIB_HPP_ */
