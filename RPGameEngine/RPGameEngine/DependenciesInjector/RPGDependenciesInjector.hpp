//
//  RPGDependenciesInjector.hpp
//  RPGameEngine
//
//  Created by Renaud Buisine on 17/08/2018.
//  Copyright © 2018 Renaud Buisine. All rights reserved.
//

#ifndef RPGDependenciesInjector_hpp
#define RPGDependenciesInjector_hpp

#include <stdio.h>
#include <unordered_map>
#include <typeindex>

class rpg_dependenciesInjector {
public:
    class injector;
    class dependency;
    
    //Public class injector
    class injector {
    public:
        friend class rpg_dependenciesInjector;
        
        //public class injectedPtr
        template<typename T = dependency>
        class injectedPtr {
        public:
            friend class rpg_dependenciesInjector;
            //injectedPtr / Public destructor
            ~injectedPtr(void) noexcept;
            
            typename std::add_rvalue_reference<T>::type operator*() const noexcept;
            T *operator->() const noexcept;
            
            //Operators
            template<typename U>
            friend bool operator==(const rpg_dependenciesInjector::injector::injectedPtr<U>& ,const U *);
            template<typename U>
            friend bool operator==(const U *, const rpg_dependenciesInjector::injector::injectedPtr<U>&);
            template<typename U>
            friend bool operator==(const rpg_dependenciesInjector::injector::injectedPtr<U>& ,const long&);
            template<typename U>
            friend bool operator==(const long&, const rpg_dependenciesInjector::injector::injectedPtr<U>&);
        private:
            //injectedPtr / private constructor
            injectedPtr(T *, bool) noexcept;
            
            //injectedPtr / private attributes
            T *m_ptr;
            bool m_retained;
        };
        
        //injector / Public constructor/desctructor
        ~injector(void) noexcept;
        
        //injector / Public functions
        template<typename T = dependency>
        injectedPtr<T> getDependency();
    private:
        
        //injector / Private constructor/desctructor
        injector(void) noexcept;
        
        //injector / Private functions
        void clear(void) noexcept;
        
        //injector / Private attributes
        std::unordered_map<std::type_index,dependency *> m_dependencies;
    };
    
    //public class dependency
    class dependency {
        friend class rpg_dependenciesInjector::injector;
    protected:
        dependency(injector&);
        virtual ~dependency(void) = default;
    };
    
    // Public constructor/desctructor
    rpg_dependenciesInjector(void) noexcept;
    ~rpg_dependenciesInjector(void) noexcept;
    
    //Public function
    template<typename T = dependency>
    void registerDependency() noexcept;
    void clear(void) noexcept;
    
    // GETTERs
    size_t size(void) const noexcept;
    injector *getInjector(void) noexcept;
    
private:
    //Private attributes
    injector m_injector;
};

#include "RPGDependenciesInjectorImpl.hpp"
#include "RPGDependenciesInjectorInjectedPtrImpl.hpp"

#endif /* RPGDependenciesInjector_hpp */
