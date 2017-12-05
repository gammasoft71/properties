#include <properties/properties.hpp>
#include <catch/catch.hpp>
#include <memory>

using namespace properties;

TEST_CASE("GIVEN Create readwrite property THEN get it with implicit cast operator") {
  int v = 42;
  property<int> Value {
    property_get {return v;},
    property_set {v = value;}
  };
  
  REQUIRE(v == 42);
  REQUIRE(Value == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN get it with fucntor") {
  int v = 42;
  property<int> Value {
    property_get {return v;},
    property_set {v = value;}
  };
  
  REQUIRE(v == 42);
  REQUIRE(Value() == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN get it with get method") {
  int v = 42;
  property<int> Value {
    property_get {return v;},
    property_set {v = value;}
  };
  
  REQUIRE(v == 42);
  REQUIRE(Value.get() == 42);
}

TEST_CASE("GIVEN Create readwrite property THEN check inequality operator") {
  int v = 42;
  property<int> Value {
    property_get {return v;},
    property_set {v = value;}
  };
  
  REQUIRE(v != 84);
  REQUIRE(Value != 84);
}

TEST_CASE("GIVEN Create readwrite property WHEN set it THEN get it") {
  int v = 42;
  property<int> Value {
    property_get {return v;},
    property_set {v = value;}
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
  class property_read_write {
  public:
    property_read_write() {}
    property_read_write(const property_read_write& prw) : name_(prw.name_) {}
    property_read_write& operator=(const property_read_write&) = default;
    
    property<std::string> name {
      property_get {return this->name_;},
      property_set {this->name_ = value;}
    };
    
  private:
    std::string name_ = "Test property";
  };
}

TEST_CASE("GIVEN Create readwrite property WHEN using copy constructor THEN check property was not copied") {
  std::shared_ptr<property_read_write> property_read_write1 = std::make_shared<property_read_write>();
  std::shared_ptr<property_read_write> property_read_write2 = std::make_shared<property_read_write>(*property_read_write1);
  property_read_write1 = nullptr;
  REQUIRE(property_read_write2->name == "Test property");
  property_read_write2->name = "Other thing";
  REQUIRE(property_read_write2->name == "Other thing");
}

TEST_CASE("GIVEN Create readwrite property WHEN using copy opearotor THEN check property was not copied") {
  std::shared_ptr<property_read_write> property_read_write1 = std::make_shared<property_read_write>();
  std::shared_ptr<property_read_write> property_read_write2 = std::make_shared<property_read_write>();
  *property_read_write2 = *property_read_write1;
  property_read_write1 = nullptr;
  REQUIRE(property_read_write2->name == "Test property");
  property_read_write2->name = "Other thing";
  REQUIRE(property_read_write2->name == "Other thing");
}
