#include <properties/properties.hpp>
#include <iostream>
#include <memory>
#include <string>

using namespace properties;

class writer {
public:
  ~writer() {}
  virtual void write(const std::string& s) = 0;
  virtual void write_line(const std::string& s) = 0;
};

class console_writer : public writer {
public:
  void write(const std::string& s) override {
    std::cout << s;
  }
  
  void write_line(const std::string& s) override {
    write(s);
    std::cout << std::endl;
  }
};

class test_writer {
public:
  test_writer() = default;
  
  property<std::shared_ptr<::writer>, writeonly> writer {
    property_set {
      this->writer_ = value;
      this->writer_->write_line("set new writer...");
    }
  };
  
  void do_something() {
    if(this->writer_ != nullptr)
      this->writer_->write_line("do_something...");
  }
  
  void do_otherthing() {
    if(this->writer_ != nullptr)
      this->writer_->write_line("do_otherthing...");
  }
  
private:
  std::shared_ptr<::writer> writer_;
};

int main(int argc, char* argv[]) {
  test_writer tw;
  
  std::cout << "test_writer without writer :" << std::endl;
  tw.do_something();
  tw.do_otherthing();
  std::cout << std::endl;
  
  std::cout << "test_writer with console_writer :" << std::endl;
  tw.writer = std::make_shared<console_writer>();
  tw.do_something();
  tw.do_otherthing();
  std::cout << std::endl;
}

// This code produces the following output :
//
// test_writer without writer :
//
// test_writer with console_writer :
// set new writer...
// do_something...
// do_otherthing...
