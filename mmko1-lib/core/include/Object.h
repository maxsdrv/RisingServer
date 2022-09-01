#pragma once

#include <memory>
#include <iostream>
#include <unmmko1.h>
#include <boost/noncopyable.hpp>

/* static template class for creating Default Object */

class Object : private boost::noncopyable {
public:
	template<class TReturnType>
	constexpr static std::shared_ptr<TReturnType> CreateDefaultObject() {
		return std::make_shared<TReturnType>();
	}

	template<class TReturnType>
	constexpr static std::shared_ptr<TReturnType> CreateDefaultObject(unmmko1_bus bus) {
		return std::make_shared<TReturnType>(bus);
	}
};

