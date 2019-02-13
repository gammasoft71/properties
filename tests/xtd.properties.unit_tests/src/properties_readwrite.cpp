#include <xtd/properties.hpp>
#include <catch/catch.hpp>
#include <memory>

TEST_CASE("GIVEN Create readwrite property THEN get it with implicit cast operator") {
  int v = 42;
  property_<int> Value {
    get_ {return v;},
    set_ {v = value;}
  };

  REQUIRE(v == 42);
  REQUIRE(Value == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN get it with fucntor") {
  int v = 42;
  property_<int> Value {
    get_ {return v;},
    set_ {v = value;}
  };

  REQUIRE(v == 42);
  REQUIRE(Value() == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN get it with get method") {
  int v = 42;
  property_<int> Value {
    get_ {return v;},
    set_ {v = value;}
  };

  REQUIRE(v == 42);
  REQUIRE(Value.get() == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN check inequality operator") {
  int v = 42;
  property_<int> Value {
    get_ {return v;},
    set_ {v = value;}
  };

  REQUIRE(v != 84);
  REQUIRE(Value != 84);
}

TEST_CASE("GIVEN Create readwrite property WHEN set it THEN get it") {
  int v = 42;
  property_<int> Value {
    get_ {return v;},
    set_ {v = value;}
  };

  Value = 24;
  REQUIRE(v == 24);

  Value(48);
  REQUIRE(v == 48);

  Value.set(84);
  REQUIRE(Value == 84);
  REQUIRE(v == 84);
}

namespace {
  class PropertyReadWrite {
  public:
    PropertyReadWrite() {}
    PropertyReadWrite(const PropertyReadWrite& prw) : name(prw.name) {}
    PropertyReadWrite& operator=(const PropertyReadWrite&) = default;

    property_<std::string> Name {
      get_ {return this->name;},
      set_ {this->name = value;}
    };

  private:
    std::string name = "Test property";
  };
}

TEST_CASE("GIVEN Create readwrite property WHEN using copy constructor THEN check property_ was not copied") {
  std::shared_ptr<PropertyReadWrite> propertyReadWrite1 = std::make_shared<PropertyReadWrite>();
  std::shared_ptr<PropertyReadWrite> propertyReadWrite2 = std::make_shared<PropertyReadWrite>(*propertyReadWrite1);
  propertyReadWrite1 = nullptr;
  REQUIRE(propertyReadWrite2->Name == "Test property");
  propertyReadWrite2->Name = "Other thing";
  REQUIRE(propertyReadWrite2->Name == "Other thing");
}

TEST_CASE("GIVEN Create readwrite property WHEN using copy opearotor THEN check property_ was not copied") {
  std::shared_ptr<PropertyReadWrite> propertyReadWrite1 = std::make_shared<PropertyReadWrite>();
  std::shared_ptr<PropertyReadWrite> propertyReadWrite2 = std::make_shared<PropertyReadWrite>();
  *propertyReadWrite2 = *propertyReadWrite1;
  propertyReadWrite1 = nullptr;
  REQUIRE(propertyReadWrite2->Name == "Test property");
  propertyReadWrite2->Name = "Other thing";
  REQUIRE(propertyReadWrite2->Name == "Other thing");
}
