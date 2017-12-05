/// @file
/// @brief Contains property class, #property_get and #property_set keywords.
#pragma once

#include <functional>
#include <ostream>

/// @defgroup Keywords Keywords
/// @brief Keywords are predefined, reserved identifiers that have special meanings to the compiler. They cannot be used as identifiers in your program unless they include @ as a prefix. For example, @@if is a valid identifier, but if is not because if is a keyword.

/// @brief The properties namespace contains all properties classes.
namespace properties {
  /// @brief readonly struct represent a property read only attribute.
  struct readonly {};
  
  /// @brief writeonly struct represent a property write only attributex.
  struct readwrite {};
  
  /// @brief readwrite struct represent a property read write attribute.
  struct writeonly {};
  
  /// @cond
  template <class T, class attribute_type = readwrite>
  class property;
  /// @endcond
  
  /// @brief A property is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
  /// @remarks The copy constructor is deleted. So the copy constructor of the owner class must be specified (the implicit or default copy contructor doesn't build).
  /// @par Examples
  /// This sample shows a Person class that has two properties: name (std::string) and age (int). Both properties are read/write.
  /// @include person.cpp
  template <class T, class attribute_type>
  class property : public attribute_type {
    using getter_type = std::function<T()>;
    using setter_type = std::function<void(T)>;
    
  public:
    /// @brief This method is an accessor method that retrieves the value of the property or the indexer element.
    T get() const {return this->getter();}
    
    /// @brief This operator is an accessor operator that retrieves the value of the property or the indexer element.
    T operator()() const {return this->getter();}
    
    /// @brief This method is an accessor method that assigns the value of the property or the indexer element.
    T set(T value) {this->setter(value); return this->getter();}
    
    /// @brief This operator is an accessor operator that assigns the value of the property or the indexer element.
    T operator()(T value) {this->setter(value); return this->getter();}
    
    /// @cond
    property(const getter_type& getter, const setter_type& setter) : getter(getter), setter(setter) {}
    
    operator T() const {return this->getter();}
    property& operator=(const property& property) {this->setter(property.getter()); return *this;}
    
    bool operator==(T value) const {return this->getter() == value;}
    bool operator !=(T value) const {return this->getter() != value;}
    
    property& operator=(T value) {this->setter(value); return *this;}
    void operator+=(T value) {this->setter(this->getter() + value);}
    void operator-=(T value) {this->setter(this->getter() - value);}
    void operator*=(T value) {this->setter(this->getter() * value);}
    void operator /=(T value) {this->setter(this->getter() / value);}
    void operator %=(T value) {this->setter(this->getter() % value);}
    void operator &=(T value) {this->setter(this->getter() & value);}
    void operator |=(T value) {this->setter(this->getter() | value);}
    void operator ^=(T value) {this->setter(this->getter() ^ value);}
    void operator<<=(T value) {this->setter(this->getter() << value);}
    void operator>>=(T value) {this->setter(this->getter() >> value);}
    
    friend std::ostream& operator<<(std::ostream& os, const property& p) {return os <<  p();}
    /// @endcond
    
  private:
    property(const property& property)  = delete;
    getter_type getter;
    setter_type setter;
  };
  
  /// @cond
  template <class T>
  class property<T, readonly> : public readonly {
    using getter_type = std::function<T()>;
    
  public:
    explicit property(const getter_type& getter) : getter(getter) {}
    property& operator=(const property& property) {return *this;}
    
    T get() const {return this->getter();}
    T operator()() const {return this->getter();}
    operator T() const { return this->getter(); }
    operator T() { return this->getter(); }
    bool operator==(T value) const {return this->getter() == value;}
    bool operator !=(T value) const {return this->getter() != value;}
    
    friend std::ostream& operator<<(std::ostream& os, const property& p) {return os <<  p();}
    
  private:
    property(const property& property)  = delete;
    getter_type getter;
  };
  
  template <class T>
  class property<T, writeonly> : public writeonly {
    using setter_type = std::function<void(T)>;
    
  public:
    explicit property(const setter_type& setter) : setter(setter) {}
    property& operator=(const property& property) {return *this;}
    
    void set(T value) {this->setter(value);}
    void operator()(T value) {this->setter(value);}
    void operator=(T value) {this->setter(value);}
    
  private:
    property(const property& property)  = delete;
    setter_type setter;
  };
  /// @endcond
  
  
  /// @brief The property_get keyword defines an accessor method in a property or indexer that retrieves the value of the property or the indexer element.
  /// @par Examples
  /// @code
  /// class person {
  /// public:
  ///   person() {}
  ///   person(const person& p) : name(p.name) {}
  ///
  ///   property<std::string> Name {
  ///     property_get {return this->name},
  ///     property_set {std::transform(value.begin(), value.end(), std::back_inserter(this->name), ::toupper);}
  ///   };
  ///
  /// private:
  ///   std::string name;
  /// };
  /// @endcode
  /// @ingroup Keywords
#define property_get \
  [&]()
  
  /// @brief The property_set keyword defines an accessor method in a property or indexer that assigns the value of the property or the indexer element.
  /// @par Examples
  /// @code
  /// class person {
  /// public:
  ///   person() {}
  ///   person(const person& p) : name(p.name) {}
  ///
  ///   property<std::string> Name {
  ///     property_get {return this->name},
  ///     property_set {std::transform(value.begin(), value.end(), std::back_inserter(this->name), ::toupper);}
  ///   };
  ///
  /// private:
  ///   std::string name;
  /// };
  /// @endcode
  /// @ingroup Keywords
#define property_set \
  [&](const auto& value)
}


/// @mainpage properties - Reference Guide
///
/// @section properties_section properties
///   * <b>properties</b> add c#-like property accessor to your c++ class.
///   * <b>properties</b> is distributed as a single header file.
///
/// @section what_section What is it ?
/// A property is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
///
/// @section types_section There are three types of properties :
///
/// @par readwrite
/// The property accessor can be read and write.
/// @code
/// class foo {
/// public:
///   ...
///
///   property<int> number {
///     property_get {return this->number_;},
///     property_set {this->number_ = value;}
///   };
///
///   ...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
///
/// @par readonly
/// The property accessor can be read only.
/// @code
/// class foo {
/// public:
///   ...
///
///   property<int, readonly> number {
///     property_get {return this->number_;}
///   };
///
///   ...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
///
/// @par writeonly
/// The property accessor can be write only.
/// @code
/// class foo {
/// public:
///   ...
///
///   property<int, writeonly> number {
///     property_set {this->number_ = value;}
///   };
///
///   ...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
