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
    
    //Public class injector
    class injector {
    public:
        friend class rpg_dependenciesInjector;
        
        //public class unretainedDependency
        template<typename T>
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
        template<typename T>
        injectedPtr<T> getDependency() noexcept;
    private:
        //private class dependency
        struct dependency {
            friend class rpg_dependenciesInjector;
            virtual ~dependency(void) noexcept = default;
            
            virtual void *getInstance(void) const { return NULL; }
            virtual void *callFactory(injector&) const { return NULL; }
            virtual bool shouldRetain(void) const { return false; }
        };
        
        //private class unretainedDependency
        template<typename T>
        class unretainedDependency: dependency {
        public:
            friend class rpg_dependenciesInjector;
            //unretainedDependency / public constructor/desctructor
            unretainedDependency(T *(*)(injector&), bool) noexcept;
            ~unretainedDependency(void) noexcept = default;
            
            void *callFactory(injector&) const override final;
            bool shouldRetain(void) const override final;
        private:
            //dependency / Private attributes
            T *(*m_factory)(injector&);
            bool m_shouldRetain;
        };
        
        //Private class dependency
        template<typename T>
        class retainedDependency: dependency {
        public:
            friend class rpg_dependenciesInjector;
            //retainedDependency / public constructor/desctructor
            retainedDependency(T *inst) noexcept;
            ~retainedDependency(void) noexcept;
            
            void * getInstance(void) const override final;
        private:
            //retainedDependency / Private attributes
            T *m_inst;
        };
        
        //injector / Private constructor/desctructor
        injector(void) noexcept;
        
        //injector / Private functions
        void clear(void) noexcept;
        
        //injector / Private attributes
        std::unordered_map<std::type_index,dependency *> m_dependencies;
    };
    
    // Public constructor/desctructor
    rpg_dependenciesInjector(void) noexcept;
    ~rpg_dependenciesInjector(void) noexcept;
    
    //Public function
    template<typename T>
    void registerDependency(T *(*)(rpg_dependenciesInjector::injector&), bool = false) noexcept;
    void clear(void) noexcept;
    
    // GETTERs
    size_t size(void) const noexcept;
    injector *getInjector(void) noexcept;
    
private:
    //Private attributes
    injector m_injector;
};

#include "RPGDependenciesInjectorImpl.hpp"
#include "RPGDependenciesInjectorRetainedDependencyImpl.hpp"
#include "RPGDependenciesInjectorUnretainedDependencyImpl.hpp"
#include "RPGDependenciesInjectorInjectedPtrImpl.hpp"

#endif /* RPGDependenciesInjector_hpp */
