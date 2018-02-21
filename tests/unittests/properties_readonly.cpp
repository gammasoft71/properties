#include <properties/properties.hpp>
#include <catch/catch.hpp>

TEST_CASE("GIVEN Create readonly property THEN get it with implicit cast operator") {
  int v = 42;
  property_<int, readonly_> Value {
    get_ {return v;}
  };

  REQUIRE(Value == 42);
}

TEST_CASE("GIVEN Create readonly property THEN get it with functor") {
  int v = 42;
  property_<int, readonly_> Value {
    get_ {return v;}
  };

  REQUIRE(Value() == 42);
}

TEST_CASE("GIVEN Create readonly property THEN get it with get function") {
  int v = 42;
  property_<int, readonly_> Value {
    get_ {return v;}
  };

  REQUIRE(Value.get() == 42);
}

TEST_CASE("GIVEN Create readonly property THEN check inequality operator") {
  int v = 42;
  property_<int, readonly_> Value {
    get_ {return v;}
  };

  REQUIRE(Value != 84);
}

namespace {
  class PropertyReadOnly {
  public:
    PropertyReadOnly() {}
    PropertyReadOnly(const PropertyReadOnly& prw) : name(prw.name) {}
    PropertyReadOnly& operator=(const PropertyReadOnly& prw) = default;

    property_<std::string, readonly_> Name {
      get_ {return this->name;}
    };

  private:
    std::string name = "Test property";
  };
}

TEST_CASE("GIVEN Create readonly property WHEN using copy constructor THEN check property_ was not copied") {
  std::shared_ptr<PropertyReadOnly> propertyReadOnly1 = std::make_shared<PropertyReadOnly>();
  std::shared_ptr<PropertyReadOnly> propertyReadOnly2 = std::make_shared<PropertyReadOnly>(*propertyReadOnly1);
  propertyReadOnly1 = nullptr;
  REQUIRE(propertyReadOnly2->Name == "Test property");
}

TEST_CASE("GIVEN Create readonly property WHEN using copy opearotor THEN check property_ was not copied") {
  std::shared_ptr<PropertyReadOnly> propertyReadOnly1 = std::make_shared<PropertyReadOnly>();
  std::shared_ptr<PropertyReadOnly> property_read_write2 = std::make_shared<PropertyReadOnly>();
  *property_read_write2 = *propertyReadOnly1;
  propertyReadOnly1 = nullptr;
  REQUIRE(property_read_write2->Name == "Test property");
}
