#include <xtd/properties>
#include <xtd/xtd.tunit>

using namespace xtd;
using namespace xtd::tunit;

namespace unit_tests {
  class test_class_(test_read_write_property) {
  public:
    void test_method_(create_with_implicit_cast_operator) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      assert::are_equal(42, v);
      assert::are_equal(42, value);
    }
    
    void test_method_(get_functor) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      assert::are_equal(42, v);
      assert::are_equal(42, value());
    }
    
    void test_method_(get_function) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      assert::are_equal(42, v);
      assert::are_equal(42, value.get());
    }
    
    void test_method_(equality_operator) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      assert::is_true(v == 42);
      assert::is_true(value == 42);
      assert::is_false(v == 84);
      assert::is_false(value == 84);
    }
    
    void test_method_(inequality_operator) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      assert::is_false(v != 42);
      assert::is_false(value != 42);
      assert::is_true(v != 84);
      assert::is_true(value != 84);
    }

    void test_method_(create_and_set) {
      int v = 42;
      property_<int> value {
        get_ {return v;},
        set_ {v = value;}
      };
      
      value = 24;
      assert::are_equal(24, v);
      
      value(48);
      assert::are_equal(48, v);
      
      value.set(84);
      assert::are_equal(84, value);
      assert::are_equal(84, v);
    }
    
    class property_read_write {
    public:
      property_read_write() {}
      property_read_write(const property_read_write& prw) : name_(prw.name_) {}
      property_read_write& operator=(const property_read_write&) = default;
      
      property_<std::string> name {
        get_ {return this->name_;},
        set_ {this->name_ = value;}
      };
      
    private:
      std::string name_ = "Test property";
    };
    
    void test_method_(create_using_copy_constructor) {
      std::shared_ptr<property_read_write> property_read_write1 = std::make_shared<property_read_write>();
      std::shared_ptr<property_read_write> property_read_write2 = std::make_shared<property_read_write>(*property_read_write1);
      property_read_write1 = nullptr;

      assert::is_null(property_read_write1);
      assert::are_equal("Test property", property_read_write2->name);
      
      property_read_write2->name = "Other thing";
      
      assert::are_equal("Other thing", property_read_write2->name);
    }
    
    void test_method_(create_using_copy_operator) {
      std::shared_ptr<property_read_write> property_read_write1 = std::make_shared<property_read_write>();
      std::shared_ptr<property_read_write> property_read_write2 = std::make_shared<property_read_write>();
      *property_read_write2 = *property_read_write1;
      property_read_write1 = nullptr;
      
      assert::is_null(property_read_write1);
      assert::are_equal("Test property", property_read_write2->name);
      
      property_read_write2->name = "Other thing";
      
      assert::are_equal("Other thing", property_read_write2->name);
    }
  };
}
