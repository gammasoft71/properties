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
  template <class type_t, class attribute_t = readwrite_>
  class property_;
  /// @endcond
  
  /// @brief A property_ is a member that provides a flexible mechanism to read, write, or compute the value of a private field. Properties can be used as if they are public data members, but they are actually special methods called accessors. This enables data to be accessed easily and still helps promote the safety and flexibility of methods.
  /// @remarks The copy constructor is deleted. So the copy constructor of the owner class must be specified (the implicit or default copy contructor doesn't build).
  /// @par Examples
  /// This sample shows a Person class that has two properties: name (std::string) and age (int). Both properties are read/write.
  /// @include person.cpp
  template <class type_t>
  class property_<type_t, readwrite_> : public readwrite_ {
    using getter_type = std::function<const type_t&()>;
    using setter_type = std::function<void(const type_t&)>;
    
  public:
    /// @brief This method is an accessor method that retrieves the value of the property_ or the indexer element.
    const type_t& get() const {return getter();}
    
    /// @brief This operator is an accessor operator that retrieves the value of the property_ or the indexer element.
    const type_t& operator()() const {return getter();}
    
    /// @brief This method is an accessor method that assigns the value of the property_ or the indexer element.
    const type_t& set(const type_t& value) {setter(value); return getter();}
    
    /// @brief This operator is an accessor operator that assigns the value of the property_ or the indexer element.
    const type_t& operator()(const type_t& value) {setter(value); return getter();}
    
    /// @cond
    property_() = default;
    property_(const type_t& value) : value(value) {}
    property_(const getter_type& getter, const setter_type& setter) : getter(getter), setter(setter) {}
    property_(const property_& property) : value(property.value) {}
    
    operator const type_t&() const {return getter();}
    property_& operator=(const property_& property_) {setter(property_.getter()); return *this;}
    bool operator==(const type_t& value) const {return getter() == value;}
    bool operator!=(const type_t& value) const {return getter() != value;}
    
    property_& operator=(const type_t& value) {setter(value); return *this;}
    void operator+=(const type_t& value) {setter(getter() + value);}
    void operator-=(const type_t& value) {setter(getter() - value);}
    void operator*=(const type_t& value) {setter(getter() * value);}
    void operator /=(const type_t& value) {setter(getter() / value);}
    void operator %=(const type_t& value) {setter(getter() % value);}
    void operator &=(const type_t& value) {setter(getter() & value);}
    void operator |=(const type_t& value) {setter(getter() | value);}
    void operator ^=(const type_t& value) {setter(getter() ^ value);}
    void operator<<=(const type_t& value) {setter(getter() << value);}
    void operator>>=(const type_t& value) {setter(getter() >> value);}
    
    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}
    /// @endcond
    
  private:
    type_t value = type_t();
    getter_type getter = [&] {return value;};
    setter_type setter = [&](const type_t& value) {this->value = value;};
  };
  
  /// @cond
  template <class type_t, class attribute_t>
  class property_ {
    using getter_type = std::function<const type_t&()>;
    using setter_type = std::function<void(const type_t&)>;
    
    friend attribute_t;
    
  public:
    const type_t& get() const {return getter();}
    
    const type_t& operator()() const {return getter();}
    
  private:
    const type_t& set(const type_t& value) {setter(value); return getter();}
    
    const type_t& operator()(const type_t& value) {setter(value); return getter();}
    
  public:
    property_() = default;
    property_(const type_t& value) : value(value) {}
    property_(const getter_type& getter, const setter_type& setter) : getter(getter), setter(setter) {}
    property_(const property_& property) : value(property.value) {}
    
    operator type_t() const {return getter();}
  private:
    property_& operator=(const property_& property_) {setter(property_.getter()); return *this;}
  public:
    bool operator==(const type_t& value) const {return getter() == value;}
    bool operator!=(const type_t& value) const {return getter() != value;}
    
  private:
    property_& operator=(const type_t& value) {setter(value); return *this;}
    void operator+=(const type_t& value) {setter(getter() + value);}
    void operator-=(const type_t& value) {setter(getter() - value);}
    void operator*=(const type_t& value) {setter(getter() * value);}
    void operator /=(const type_t& value) {setter(getter() / value);}
    void operator %=(const type_t& value) {setter(getter() % value);}
    void operator &=(const type_t& value) {setter(getter() & value);}
    void operator |=(const type_t& value) {setter(getter() | value);}
    void operator ^=(const type_t& value) {setter(getter() ^ value);}
    void operator<<=(const type_t& value) {setter(getter() << value);}
    void operator>>=(const type_t& value) {setter(getter() >> value);}
    
  public:
    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}
    
  private:
    type_t value = type_t();
    getter_type getter = [&] {return value;};
    setter_type setter = [&](const type_t& value) {this->value = value;};
  };
  
  template <class type_t>
  class property_<type_t, readonly_> : public readonly_ {
    using getter_type = std::function<const type_t&()>;
    
  public:
    explicit property_(const getter_type& getter) : getter(getter) {}
    property_& operator=(const property_& property_) {return *this;}
    
    const type_t& get() const {return getter();}
    const type_t& operator()() const {return getter();}
    operator type_t() const { return getter(); }
    operator type_t() { return getter(); }
    bool operator==(const type_t& value) const {return getter() == value;}
    bool operator !=(const type_t& value) const {return getter() != value;}
    
    friend std::ostream& operator<<(std::ostream& os, const property_& p) {return os <<  p();}
    
  private:
    property_(const property_& property_)  = delete;
    getter_type getter;
  };
  
  template <class type_t>
  class property_<type_t, writeonly_> : public writeonly_ {
    using setter_type = std::function<void(type_t)>;
    
  public:
    explicit property_(const setter_type& setter) : setter(setter) {}
    property_& operator=(const property_& property_) {return *this;}
    
    void set(const type_t& value) {setter(value);}
    void operator()(const type_t& value) {setter(value);}
    void operator=(const type_t& value) {setter(value);}
    
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
  ///     get_ {return name},
  ///     set_ {std::transform(value.begin(), value.end(), std::back_inserter(name), ::toupper);}
  ///   };
  ///
  /// private:
  ///   std::string name;
  /// };
  /// @endcode
  /// @ingroup keywords
#define get_ \
  [&]() -> const auto&
  
  /// @brief The #set_ keyword defines an accessor method in a property_ or indexer that assigns the value of the property_ or the indexer element.
  /// @par Examples
  /// @code
  /// class Person {
  /// public:
  ///   Person() {}
  ///   Person(const Person& p) : name_(p.name) {}
  ///
  ///   property_<std::string> Name {
  ///     get_ {return name},
  ///     set_ {std::transform(value.begin(), value.end(), std::back_inserter(name), ::toupper);}
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
/// class foo {
/// public:
///   //...
///
///   property_<int> number {
///     get_ {return number_;},
///     set_ {number_ = value;}
///   };
///
///   //...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
///
/// @par readonly_
/// The property_ accessor can be read only.
/// @code
/// class foo {
/// public:
///   //...
///
///   property_<int, readonly_> number {
///     get_ {return number_;}
///   };
///
///   //...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
///
/// @par writeonly_
/// The property_ accessor can be write only.
/// @code
/// class foo {
/// public:
///   //...
///
///   property_<int, writeonly_> number {
///     set_ {number_ = value;}
///   };
///
///   //...
///
/// private:
///   int number_ = 0;
/// };
/// @endcode
