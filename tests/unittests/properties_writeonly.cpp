#include <properties/properties.hpp>
#include <catch/catch.hpp>

using namespace properties;

TEST_CASE("GIVEN create writeonly property WHEN Set with equal operator then THEN check value") {
  int v = 42;
  property_<int, writeonly_> Value {
    set_ {v = value;}
  };
  
  Value = 24;
  REQUIRE(v == 24);
}

TEST_CASE("GIVEN create writeonly property WHEN Set with functor then THEN check value") {
  int v = 42;
  property_<int, writeonly_> Value {
    set_ {v = value;}
  };
  
  Value(24);
  REQUIRE(v == 24);
}

TEST_CASE("GIVEN create writeonly property WHEN Set with set method then THEN check value") {
  int v = 42;
  property_<int, writeonly_> Value {
    set_ {v = value;}
  };
  
  Value.set(24);
  REQUIRE(v == 24);
}

namespace {
  class PropertyWriteOnly {
  public:
    PropertyWriteOnly() {}
    PropertyWriteOnly(const PropertyWriteOnly& prw) : name(prw.name) {}
    PropertyWriteOnly& operator=(const PropertyWriteOnly& prw) = default;
    
    property_<std::string, writeonly_> Name {
      set_ {this->name = value;}
    };
    
    std::string name = "Test property";
  };
}

TEST_CASE("GIVEN Create writeonly property WHEN using copy constructor THEN check property_ was not copied") {
  std::shared_ptr<PropertyWriteOnly> propertyWriteOnly1 = std::make_shared<PropertyWriteOnly>();
  std::shared_ptr<PropertyWriteOnly> propertyWriteOnly2 = std::make_shared<PropertyWriteOnly>(*propertyWriteOnly1);
  propertyWriteOnly1 = nullptr;
  REQUIRE(propertyWriteOnly2->name == "Test property");
  propertyWriteOnly2->Name = "Other thing";
  REQUIRE(propertyWriteOnly2->name == "Other thing");
}

TEST_CASE("GIVEN Create writeonly property WHEN using copy opearotor THEN check property_ was not copied") {
  std::shared_ptr<PropertyWriteOnly> propertyWriteOnly1 = std::make_shared<PropertyWriteOnly>();
  std::shared_ptr<PropertyWriteOnly> propertyWriteOnly2 = std::make_shared<PropertyWriteOnly>();
  *propertyWriteOnly2 = *propertyWriteOnly1;
  propertyWriteOnly1 = nullptr;
  REQUIRE(propertyWriteOnly2->name == "Test property");
  propertyWriteOnly2->Name = "Other thing";
  REQUIRE(propertyWriteOnly2->name == "Other thing");
}
