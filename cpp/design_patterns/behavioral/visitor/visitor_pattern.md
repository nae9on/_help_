# Visitor pattern

The visitor pattern is a behavioral design pattern that allows separating an algorithm from an object structure on
which it operates. https://en.wikipedia.org/wiki/Visitor_pattern



#### Rule of thumb

- Limited applicability

- From [SO](https://stackoverflow.com/questions/9949110/pattern-to-avoid-dynamic-cast) - visitor pattern is an alternative to virtual functions and should be used when the later is not feasible
   
  There's cases where one is better, and cases where the other is. Usually, the rule of thumb goes like this:
  
  - If you have a rather **fixed set of operations**, but keep **adding types**, use **virtual functions**.
     Operations are hard to add to/remove from a big inheritance hierarchy,  but new types are easy to add
     by simply having them override the  appropriate virtual functions.  
  - If you have a rather **fixed set of types**, but keep **adding operations**, use the **[visitor pattern](http://en.wikipedia.org/wiki/Visitor_pattern)**.
     Adding new types to a large set of visitors is a serious pain in the neck, but adding a new visitor to a
     fixed set of types is easy. 



#### Applications

1. AST

2. XML structures - `tinyxml.h` is using visitor pattern see `TiXmlVisitor`

   I read that the XML structure is a typical use case of Visitor pattern where the number of types of nodes is limited
   (from code I see we have 6 type `TiXmlDocument`, `TiXmlElement`, `TiXmlDeclaration`, `TiXmlText`, `TiXmlComment` and `TiXmlUnknown`)

   While the number of operations on these nodes can be many more (example pretty print, count children, delete node etc.)
   The pattern allows adding new operations without changing the 6 types (which is stable library code).



#### When to use?

1. To add new operations to existing object structures without modifying the structures.
2. When a class hierarchy is stable in its breadth (i.e. fixed number of derived classes) but not stable in
   its depth (i.e. all methods/operations are not known in advance and can grow/change over time)
3. Library code where it is not feasible to add new methods.



#### Client code

1. Client simply calls the `Accept()` on each node with the correct type of Visitor. The visitor visits the node and performs an action.
2. Different visitors can be implemented who will do different things when visiting the nodes. The client
   does not 



#### Pros

New operations can be added without changing the library code by simply implementing new visitors



#### Cons

Bad OO - moves op's away from data
Visitor cannot access the private data of the class hierarchy
Adding a new node type to class hierarchy => all visitors need to implement their visit of that node type

