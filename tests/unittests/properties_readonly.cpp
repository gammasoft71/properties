#include <properties/properties.hpp>
#include <catch/catch.hpp>

using namespace properties;

TEST_CASE("GIVEN Create readonly property THEN get it with implicit cast operator") {
  int v = 42;
  property<int, readonly> Value {
    property_get {return v;}
  };
  
  REQUIRE(Value == 42);
}

TEST_CASE("GIVEN Create readonly property THEN get it with functor") {
  int v = 42;
  property<int, readonly> Value {
    property_get {return v;}
  };
  
  REQUIRE(Value() == 42);
}

TEST_CASE("GIVEN Create readonly property THEN get it with get function") {
  int v = 42;
  property<int, readonly> Value {
    property_get {return v;}
  };
  
  REQUIRE(Value.get() == 42);
}

TEST_CASE("GIVEN Create readonly property THEN check inequality operator") {
  int v = 42;
  property<int, readonly> Value {
    property_get {return v;}
  };
  
  REQUIRE(Value != 84);
}

namespace {
  class property_read_only {
  public:
    property_read_only() {}
    property_read_only(const property_read_only& prw) : name_(prw.name_) {}
    property_read_only& operator=(const property_read_only& prw) = default;
    
    property<std::string, readonly> name {
      property_get {return this->name_;}
    };
    
  private:
    std::string name_ = "Test property";
  };
}

TEST_CASE("GIVEN Create readonly property WHEN using copy constructor THEN check property was not copied") {
  std::shared_ptr<property_read_only> property_read_only1 = std::make_shared<property_read_only>();
  std::shared_ptr<property_read_only> property_read_only2 = std::make_shared<property_read_only>(*property_read_only1);
  property_read_only1 = nullptr;
  REQUIRE(property_read_only2->name == "Test property");
}

TEST_CASE("GIVEN Create readonly property WHEN using copy opearotor THEN check property was not copied") {
  std::shared_ptr<property_read_only> property_read_only1 = std::make_shared<property_read_only>();
  std::shared_ptr<property_read_only> property_read_write2 = std::make_shared<property_read_only>();
  *property_read_write2 = *property_read_only1;
  property_read_only1 = nullptr;
  REQUIRE(property_read_write2->name == "Test property");
}
