#include <iostream>
#include <vector>
#include <sstream>
#include <memory>

class HtmlBuilder;

class HtmlElement {

public:
  std::string name;
  std::string text;
  std::vector<HtmlElement> elements;
  const size_t indent_size = 2;

  HtmlElement() {}
  HtmlElement(const std::string& name, const std::string& text)
    : name(name),
      text(text) {
  }

  std::string str(int indent = 0) const {
    std::ostringstream oss;
    std::string i(indent_size*indent, ' ');

    oss << i << "<" << name << ">" << std::endl;
    if (text.size() > 0)
      oss << std::string(indent_size*(indent + 1), ' ') << text << std::endl;

    for (const auto& e : elements)
      oss << e.str(indent + 1);

    oss << i << "</" << name << ">" << std::endl;
    return oss.str();
  }

  static std::unique_ptr<HtmlBuilder> build(std::string root_name) {
    return std::make_unique<HtmlBuilder>(root_name);
  }

  // static HtmlBuilder build(std::string root_name) {
  //   return {root_name};
  // }

};

class HtmlBuilder {
  
public:
  HtmlElement root;
  HtmlBuilder(std::string root_name) {
    root.name = root_name;
  }

  // void to start with
  HtmlBuilder& add_child(std::string child_name, std::string child_text)
  {
    // HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(child_name, child_text);
    return *this;
  }

  // pointer based
  HtmlBuilder* add_child_2(std::string child_name, std::string child_text){
    // HtmlElement e{ child_name, child_text };
    root.elements.emplace_back(child_name, child_text );
    return this;
  }

  std::string str() { return root.str(); }

  operator HtmlElement() const { return root; }
};

int main() {

  HtmlBuilder builder{ "ul" };
  builder.add_child("li", "hello").add_child("li", "world");
  std::cout << builder.str() << std::endl;


  // auto builder2 = HtmlElement::build("ul")
  //   ->add_child_2("li", "hello")->add_child_2("li", "world");
  // std::cout << builder2 << std::endl;
  return 0;
}