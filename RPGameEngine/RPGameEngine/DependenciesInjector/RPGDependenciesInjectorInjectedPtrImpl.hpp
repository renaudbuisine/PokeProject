//
//  RPGDependenciesInjectorInjectedPtrImpl.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 19/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDependenciesInjectorInjectedPtrImpl_hpp
#define RPGDependenciesInjectorInjectedPtrImpl_hpp

// CONSTRUCTOR

template<typename T>
rpg_dependenciesInjector::injector::injectedPtr<T>::injectedPtr(T *ptr, bool isRetained) noexcept: m_ptr(ptr), m_retained(isRetained) { }

template<typename T>
rpg_dependenciesInjector::injector::injectedPtr<T>::~injectedPtr(void) noexcept {
    if(!m_retained) {
        delete(m_ptr);
    }
}

// OPERATORS

template<typename T>
T *rpg_dependenciesInjector::injector::injectedPtr<T>::operator->() const noexcept {
    return m_ptr;
}

template<typename T>
typename std::add_rvalue_reference<T>::type rpg_dependenciesInjector::injector::injectedPtr<T>::operator*() const noexcept {
    return *m_ptr;
}


template<typename U>
bool operator==(const rpg_dependenciesInjector::injector::injectedPtr<U>& lhs ,const U *rhs) {
    return lhs.m_ptr == rhs;
}

template<typename U>
bool operator==(const U *lhs, const rpg_dependenciesInjector::injector::injectedPtr<U>& rhs) {
    return rhs == lhs;
}

template<typename U>
bool operator==(const rpg_dependenciesInjector::injector::injectedPtr<U>& lhs ,const long& rhs) {
    return lhs.m_ptr == (U *)rhs;
}

template<typename U>
bool operator==(const long& lhs, const rpg_dependenciesInjector::injector::injectedPtr<U>& rhs) {
    return rhs == lhs;
}

#endif /* RPGDependenciesInjectorInjectedPtrImpl_hpp */
