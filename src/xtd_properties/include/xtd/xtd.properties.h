/// @file
/// @brief Contains property_ class, #get_ and #set_ keywords.
#pragma once

#include <functional>
#include <ostream>

/// @defgroup keywords keywords
/// @brief Keywords are predefined, reserved identifiers that have special meanings to the compiler.

/// @brief The xtd namespace contains all fundamental classes to access Hardware, Os, System, and more.
namespace xtd {
  /// @brief readonly_ struct represent a property_ read only attribute.
  struct readonly_ {};

  /// @brief writeonly_ struct represent a property_ write only attributex.
  struct readwrite_ {};

  /// @brief readwrite_ struct represent a property_ read write attribute.
  struct writeonly_ {};

  /// @cond
  template <class T, class attribute_type = readwrite_>
  class property_;
  /// @endcond

  /// @brief A property_ is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
  /// @remarks The copy constructor is deleted. So the copy constructor of the owner class must be specified (the implicit or default copy contructor doesn't build).
  /// @par Examples
  /// This sample shows a Person class that has two properties: name (std::string) and age (int). Both properties are read/write.
  /// @include person.cpp
  template <class T>
  class property_<T, readwrite_> : public readwrite_ {
    using getter_type = std::function<T()>;
    using setter_type = std::function<void(T)>;
    
  public:
    /// @brief This method is an accessor method that retrieves the value of the property_ or the indexer element.
    T get() const {return this->getter();}
    
    /// @brief This operator is an accessor operator that retrieves the value of the property_ or the indexer element.
    T operator()() const {return this->getter();}
    
    /// @brief This method is an accessor method that assigns the value of the property_ or the indexer element.
    T set(T value) {this->setter(value); return this->getter();}
    
    /// @brief This operator is an accessor operator that assigns the value of the property_ or the indexer element.
    T operator()(T value) {this->setter(value); return this->getter();}
    
    /// @cond
    property_() = default;
    property_(T value) : value(value) {}
    property_(const getter_type& getter, const setter_type& setter) : getter(getter), setter(setter) {}
    property_(const property_& property) : value(property.value) {}
    
    operator T() const {return this->getter();}
    property_& operator=(const property_& property_) {this->setter(property_.getter()); return *this;}
    bool operator==(T value) const {return this->getter() == value;}
    bool operator!=(T value) const {return this->getter() != value;}
    
    property_& operator=(T value) {this->setter(value); return *this;}
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
    
    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}
    /// @endcond
    
  private:
    T value = T();
    getter_type getter = [&] {return this->value;};
    setter_type setter = [&](const T& value) {this->value = value;};
  };

  /// @cond
  template <class T, class attribute_type>
  class property_ {
    using getter_type = std::function<T()>;
    using setter_type = std::function<void(T)>;
    
    friend attribute_type;
    
  public:
    T get() const {return this->getter();}
    
    T operator()() const {return this->getter();}
    
  private:
    T set(T value) {this->setter(value); return this->getter();}
    
    T operator()(T value) {this->setter(value); return this->getter();}
    
  public:
    property_() = default;
    property_(T value) : value(value) {}
    property_(const getter_type& getter, const setter_type& setter) : getter(getter), setter(setter) {}
    property_(const property_& property) : value(property.value) {}
    
    operator T() const {return this->getter();}
  private:
    property_& operator=(const property_& property_) {this->setter(property_.getter()); return *this;}
  public:
    bool operator==(T value) const {return this->getter() == value;}
    bool operator!=(T value) const {return this->getter() != value;}
    
  private:
    property_& operator=(T value) {this->setter(value); return *this;}
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
    
  public:
    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}
    
  private:
    T value = T();
    getter_type getter = [&] {return this->value;};
    setter_type setter = [&](const T& value) {this->value = value;};
  };

  template <class T>
  class property_<T, readonly_> : public readonly_ {
    using getter_type = std::function<T()>;

  public:
    explicit property_(const getter_type& getter) : getter(getter) {}
    property_& operator=(const property_& property_) {return *this;}

    T get() const {return this->getter();}
    T operator()() const {return this->getter();}
    operator T() const { return this->getter(); }
    operator T() { return this->getter(); }
    bool operator==(T value) const {return this->getter() == value;}
    bool operator !=(T value) const {return this->getter() != value;}

    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}

  private:
    property_(const property_& property_)  = delete;
    getter_type getter;
  };

  template <class T>
  class property_<T, writeonly_> : public writeonly_ {
    using setter_type = std::function<void(T)>;

  public:
    explicit property_(const setter_type& setter) : setter(setter) {}
    property_& operator=(const property_& property_) {return *this;}

    void set(T value) {this->setter(value);}
    void operator()(T value) {this->setter(value);}
    void operator=(T value) {this->setter(value);}

  private:
    property_(const property_& property_)  = delete;
    setter_type setter;
  };

  template<typename type_t>
  using property_read_only_ = property_<type_t, readonly_>;

  template<typename type_t>
  using property_read_write_only_ = property_<type_t, writeonly_>;
/// @endcond

  /// @brief A #property_ is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
  /// @remarks The copy constructor is deleted. So the copy constructor of the owner class must be specified (the implicit or default copy contructor doesn't build).
  /// @par Examples
  /// This sample shows a Person class that has two properties: Name (string) and Age (int). Both properties are read/write.
  /// @include person.cpp
  /// @ingroup keywords
#define property_ \
  xtd::property_

  /// @brief #readonly_  represent a property_ read only attribute.
  /// @ingroup keywords
#define readonly_ \
  xtd::readonly_

  /// @brief #readwrite_  represent a property_ read write attribute.
  /// @ingroup keywords
#define readwrite_ \
  xtd::readwrite_ \

  /// @brief #writeonly_  represent a property_ write only attribute.
  /// @ingroup keywords
#define writeonly_ \
  xtd::writeonly_ \

  /// @brief The #get_ keyword defines an accessor method in a property_ or indexer that retrieves the value of the property_ or the indexer element.
  /// @par Examples
  /// @code
  /// class Person {
  /// public:
  ///   Person() {}
  ///   Person(const Person& p) : name_(p.name) {}
  ///
  ///   property_<std::string> Name {
  ///     get_ {return this->name},
  ///     set_ {std::transform(value.begin(), value.end(), std::back_inserter(this->name), ::toupper);}
  ///   };
  ///
  /// private:
  ///   std::string name;
  /// };
  /// @endcode
  /// @ingroup keywords
#define get_ \
  [&]()

  /// @brief The #set_ keyword defines an accessor method in a property_ or indexer that assigns the value of the property_ or the indexer element.
  /// @par Examples
  /// @code
  /// class Person {
  /// public:
  ///   Person() {}
  ///   Person(const Person& p) : name_(p.name) {}
  ///
  ///   property_<std::string> Name {
  ///     get_ {return this->name},
  ///     set_ {std::transform(value.begin(), value.end(), std::back_inserter(this->name), ::toupper);}
  ///   };
  ///
  /// private:
  ///   std::string name;
  /// };
  /// @endcode
  /// @ingroup keywords
#define set_ \
  [&](const auto& value)
}

/// @cond
#define property_read_only_ property_read_only_

#define property_read_write_only_ property_read_write_only_
/// @endcond

/// @mainpage properties - Reference Guide
///
/// @section properties_section properties
///   * <b>properties</b> add c#-like property_ accessor to your c++ class.
///   * <b>properties</b> is distributed as a single header file.
///
/// @section what_section What is it ?
/// A property_ is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
///
/// @section types_section There are three types of properties :
///
/// @par readwrite_
/// The property_ accessor can be read and write.
/// @code
/// class Foo {
/// public:
///   //...
///
///   property_<int> Number {
///     get_ {return this->number;},
///     set_ {this->number = value;}
///   };
///
///   //...
///
/// private:
///   int number = 0;
/// };
/// @endcode
///
/// @par readonly_
/// The property_ accessor can be read only.
/// @code
/// class Foo {
/// public:
///   //...
///
///   property_<int, readonly_> Number {
///     get_ {return this->number;}
///   };
///
///   //...
///
/// private:
///   int number = 0;
/// };
/// @endcode
///
/// @par writeonly_
/// The property_ accessor can be write only.
/// @code
/// class Foo {
/// public:
///   //...
///
///   property_<int, writeonly_> Number {
///     set_ {this->number = value;}
///   };
///
///   //...
///
/// private:
///   int number = 0;
/// };
/// @endcode
