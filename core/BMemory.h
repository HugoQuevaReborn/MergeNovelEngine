#pragma once

#include <memory>

template<typename T>
using SPointer = std::shared_ptr<T>;

template<typename T>
constexpr SPointer<T> CreateSPointer() {
	return std::make_shared<T>();
}

template<typename T>
using UPointer = std::unique_ptr<T>;

template<typename T>
constexpr UPointer<T> CreateUPointer() {
	return std::make_unique<T>();
}
