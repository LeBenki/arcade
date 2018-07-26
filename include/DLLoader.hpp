/*
** EPITECH PROJECT, 2018
** arcade
** File description:
** arcade
*/

#include <string>
#include <exception>
#include <iostream>
#include <dlfcn.h>

namespace arc
{
	class DLLoader
	{
	public:
		explicit DLLoader(const std::string &libname) : libname(libname)
		{
			this->handle = nullptr;
			this->handle = dlopen(this->libname.c_str(), RTLD_LAZY);
			if (!this->handle)
				throw std::logic_error(std::string(dlerror()));
		}
		template<typename T>
		std::unique_ptr<T> getSymbol(const std::string &name)
		{
			typedef T *(*func)();
			auto function = (func) dlsym(this->handle,
						     name.c_str());
			if (!function)
				throw std::logic_error(std::string(dlerror()));
			std::unique_ptr<T> unique(function());
			return unique;
		}
		~DLLoader()
		{
			dlclose(this->handle);
		}
	private:
		void *handle;
		std::string libname;
	};
}