/**
 * *****************************************
 * @brief 1 .High-level modules should not depend on low-level modules.
 * Both should depend on abstractions.
 * 2 . Abstractions should not depend on details.
 * Details should depend on abstractions.
 * @author Ajmal Rasi - mail@ajmalrasi.com
 * @version 0.1
 * @date 2020-01-23
 * *****************************************
 * 
 */

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

enum class Relationship {
  parent,
  child,
  sibling
};

struct Person {
  string name;
};

struct RelationshipBrowser {
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};


/**
 * @brief // low-level
 */
struct Relationships : RelationshipBrowser {
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override {
    vector<Person> result;

    for (auto&& [first, rel, second] : relations) {
      if (first.name == name && rel == Relationship::parent) {
        result.push_back(second);
      }
    }
    return result;
  }
};

/**
 * @brief high-level
 * 
 */
struct Research {
  Research(RelationshipBrowser& browser, std::string name) {
    for (auto& child : browser.find_all_children_of(name)) {
      cout << "Sidheeq has a child called " << child.name << endl;
    }
  }

//  don't do this
//  Research(const Relationships& relationships)
//  {
//    auto& relations = relationships.relations;
//    for (auto&& [first, rel, second] : relations)
//    {
//      if (first.name == "John" && rel == Relationship::parent)
//      {
//        cout << "John has a child called " << second.name << endl;
//      }
//    }
//  }
};

int main() {
  Person parent{"Sidheeq"};
  Person child1{"Rasi"}, child2{"Jumi"};

  Relationships relationships;
  relationships.add_parent_and_child(parent, child1);
  relationships.add_parent_and_child(parent, child2);

  Research _(relationships, "Sidheeq");

  return 0;
}