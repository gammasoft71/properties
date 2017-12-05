#include <properties/properties.hpp>
#include <catch/catch.hpp>

using namespace properties;

TEST_CASE("GIVEN create writeonly property WHEN Set with equal operator then THEN check value") {
  int v = 42;
  property<int, writeonly> Value {
    property_set {v = value;}
  };
  
  Value = 24;
  REQUIRE(v == 24);
}

TEST_CASE("GIVEN create writeonly property WHEN Set with functor then THEN check value") {
  int v = 42;
  property<int, writeonly> Value {
    property_set {v = value;}
  };
  
  Value(24);
  REQUIRE(v == 24);
}

TEST_CASE("GIVEN create writeonly property WHEN Set with set method then THEN check value") {
  int v = 42;
  property<int, writeonly> Value {
    property_set {v = value;}
  };
  
  Value.set(24);
  REQUIRE(v == 24);
}

namespace {
  class property_write_only {
  public:
    property_write_only() {}
    property_write_only(const property_write_only& prw) : name_(prw.name_) {}
    property_write_only& operator=(const property_write_only& prw) = default;
    
    property<std::string, writeonly> name {
      property_set {this->name_ = value;}
    };
    
    std::string name_ = "Test property";
  };
}

TEST_CASE("GIVEN Create writeonly property WHEN using copy constructor THEN check property was not copied") {
  std::shared_ptr<property_write_only> property_write_write1 = std::make_shared<property_write_only>();
  std::shared_ptr<property_write_only> property_write_write2 = std::make_shared<property_write_only>(*property_write_write1);
  property_write_write1 = nullptr;
  REQUIRE(property_write_write2->name_ == "Test property");
  property_write_write2->name = "Other thing";
  REQUIRE(property_write_write2->name_ == "Other thing");
}

TEST_CASE("GIVEN Create writeonly property WHEN using copy opearotor THEN check property was not copied") {
  std::shared_ptr<property_write_only> property_write_write1 = std::make_shared<property_write_only>();
  std::shared_ptr<property_write_only> property_write_write2 = std::make_shared<property_write_only>();
  *property_write_write2 = *property_write_write1;
  property_write_write1 = nullptr;
  REQUIRE(property_write_write2->name_ == "Test property");
  property_write_write2->name = "Other thing";
  REQUIRE(property_write_write2->name_ == "Other thing");
}
