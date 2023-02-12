---
title: "[Spring TUTORIAL] Building REST services with Spring (2)"
author: dapin1490
date: 2023-02-03T00:00:00+09:00
categories: [IT, Spring Boot]
tags: [지식, IT, Spring, Spring Boot, Gradle, Tutorial]
render_with_liquid: false
---

<style>
  .x-understand { color: #ccb833; }
  .understand { color: #0099FF; }
  .tab { white-space: pre; }
  .underline { text-decoration: underline; }
  .cancle { text-decoration: line-through; }
  .green { color: #339966; }
  figure { text-align: center; }
</style>

## Table of Contents
- [관련 글 보기](#관련-글-보기)
- [Building REST services with Spring](#building-rest-services-with-spring)
  - [What makes something RESTful?](#what-makes-something-restful)
  - [Simplifying Link Creation](#simplifying-link-creation)

\* 일부 번역기를 사용한 부분이 있음

# 관련 글 보기
- [[Spring GUIDE] Building a RESTful Web Service](https://dapin1490.github.io/satinbower/posts/it-spring-guide-01-restful-web-service/)
- [[Spring TUTORIAL] Building REST services with Spring (1)](https://dapin1490.github.io/posts/it-spring-guide-02-build-rest-service-01/)

# Building REST services with Spring
원문 보기: <https://spring.io/guides/tutorials/rest/>  
깃허브에서 보기: <https://github.com/spring-guides/tut-rest>

## What makes something RESTful?
So far, you have a web-based service that handles the core operations involving employee data. But that’s not enough to make things "RESTful".

- Pretty URLs like `/employees/3` aren't REST.
- Merely using `GET`, `POST`, etc. isn't REST.
- Having all the CRUD operations laid out isn't REST.

In fact, what we have built so far is better described as **RPC** (**Remote Procedure Call**). That’s because there is no way to know how to interact with this service. If you published this today, you’d also have to write a document or host a developer’s portal somewhere with all the details.

This statement of Roy Fielding’s may further lend a clue to the difference between **REST** and **RPC**:

I am getting frustrated by the number of people calling any HTTP-based interface a REST API. Today’s example is the SocialSite REST API. That is RPC. It screams RPC. There is so much coupling on display that it should be given an X rating.

What needs to be done to make the REST architectural style clear on the notion that hypertext is a constraint? In other words, if the engine of application state (and hence the API) is not being driven by hypertext, then it cannot be RESTful and cannot be a REST API. Period. Is there some broken manual somewhere that needs to be fixed?

— Roy Fielding  
<i><a href="https://roy.gbiv.com/untangled/2008/rest-apis-must-be-hypertext-driven">https://roy.gbiv.com/untangled/2008/rest-apis-must-be-hypertext-driven</a></i>

The side effect of NOT including hypermedia in our representations is that clients MUST hard code URIs to navigate the API. This leads to the same brittle nature that predated the rise of e-commerce on the web. It’s a signal that our JSON output needs a little help.

Introducing [Spring HATEOAS](https://spring.io/projects/spring-hateoas), a Spring project aimed at helping you write hypermedia-driven outputs. To upgrade your service to being RESTful, add this to your build:

Adding Spring HATEOAS to `dependencies` section of `pom.xml`

```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-hateoas</artifactId>
</dependency>
```


```
Gradle의 경우 build.gradle 파일 안의 디펜던시에 아래를 추가해주면 된다.
https://jeonghoon.netlify.app/Spring/SpringBoot13-hateoas/

implementation 'org.springframework.boot:spring-boot-starter-hateoas'
```

This tiny library will give us the constructs to define a RESTful service and then render it in an acceptable format for client consumption.

A critical ingredient to any RESTful service is adding links to relevant operations. To make your controller more RESTful, add links like this:

Getting a single item resource

```java
@GetMapping("/employees/{id}")
EntityModel<Employee> one(@PathVariable Long id) {

  Employee employee = repository.findById(id) //
      .orElseThrow(() -> new EmployeeNotFoundException(id));

  return EntityModel.of(employee, //
      linkTo(methodOn(EmployeeController.class).one(id)).withSelfRel(),
      linkTo(methodOn(EmployeeController.class).all()).withRel("employees"));
}
```

\* This tutorial is based on Spring MVC and uses the static helper methods from `WebMvcLinkBuilder` to build these links. If you are using Spring WebFlux in your project, you must instead use `WebFluxLinkBuilder`.

This is very similar to what we had before, but a few things have changed:

- The return type of the method has changed from `Employee` to `EntityModel<Employee>`. `EntityModel<T>` is a generic container from Spring HATEOAS that includes not only the data but a collection of links.
- `linkTo(methodOn(EmployeeController.class).one(id)).withSelfRel()` asks that Spring HATEOAS build a link to the `EmployeeController`'s `one()` method, and flag it as a [self](https://www.iana.org/assignments/link-relations/link-relations.xhtml) link.
- `linkTo(methodOn(EmployeeController.class).all()).withRel("employees")` asks Spring HATEOAS to build a link to the aggregate root, `all()`, and call it "employees".

What do we mean by "build a link"? One of Spring HATEOAS’s core types is `Link`. It includes a **URI** and a **rel** (relation). Links are what empower the web. Before the World Wide Web, other document systems would render information or links, but it was the linking of documents WITH this kind of relationship metadata that stitched the web together.

Roy Fielding encourages building APIs with the same techniques that made the web successful, and links are one of them.

If you restart the application and query the employee record of *Bilbo*, you’ll get a slightly different response than earlier:

**<span class="green">Curling prettier</span>**

When your curl output gets more complex it can become hard to read. Use this or [other tips](https://stackoverflow.com/q/27238411/5432315) to prettify the json returned by curl:

```txt
# The indicated part pipes the output to json_pp and asks it to make your JSON pretty. (Or use whatever tool you like!)
#                                  v------------------v
curl -v localhost:8080/employees/1 | json_pp
```

RESTful representation of a single employee

```json
{
  "id": 1,
  "name": "Bilbo Baggins",
  "role": "burglar",
  "_links": {
    "self": {
      "href": "http://localhost:8080/employees/1"
    },
    "employees": {
      "href": "http://localhost:8080/employees"
    }
  }
}
```

This decompressed output shows not only the data elements you saw earlier (`id`, `name` and `role`), but also a `_links` entry containing two URIs. This entire document is formatted using [HAL](http://stateless.co/hal_specification.html).

HAL is a lightweight [mediatype](https://tools.ietf.org/html/draft-kelly-json-hal-08) that allows encoding not just data but also hypermedia controls, alerting consumers to other parts of the API they can navigate toward. In this case, there is a "self" link (kind of like a `this` statement in code) along with a link back to the **[aggregate root](https://www.google.com/search?q=What+is+an+aggregate+root)**.

To make the aggregate root ALSO more RESTful, you want to include top level links while ALSO including any RESTful components within.

So we turn this

Getting an aggregate root

```java
@GetMapping("/employees")
List<Employee> all() {
  return repository.findAll();
}
```

into this

Getting an aggregate root resource

```java
@GetMapping("/employees")
CollectionModel<EntityModel<Employee>> all() {

  List<EntityModel<Employee>> employees = repository.findAll().stream()
      .map(employee -> EntityModel.of(employee,
          linkTo(methodOn(EmployeeController.class).one(employee.getId())).withSelfRel(),
          linkTo(methodOn(EmployeeController.class).all()).withRel("employees")))
      .collect(Collectors.toList());

  return CollectionModel.of(employees, linkTo(methodOn(EmployeeController.class).all()).withSelfRel());
}
```

Wow! That method, which used to just be `repository.findAll()`, is all grown up! Not to worry. Let’s unpack it.

`CollectionModel<>` is another Spring HATEOAS container; it’s aimed at encapsulating collections of resources—instead of a single resource entity, like `EntityModel<>` from earlier. `CollectionModel<>`, too, lets you include links.

Don’t let that first statement slip by. What does "encapsulating collections" mean? Collections of employees?

Not quite.

Since we’re talking REST, it should encapsulate collections of **employee resources**.

That’s why you fetch all the employees, but then transform them into a list of `EntityModel<Employee>` objects. (Thanks Java 8 Streams!)

If you restart the application and fetch the aggregate root, you can see what it looks like now.

RESTful representation of a collection of employee resources

```json
{
  "_embedded": {
    "employeeList": [
      {
        "id": 1,
        "name": "Bilbo Baggins",
        "role": "burglar",
        "_links": {
          "self": {
            "href": "http://localhost:8080/employees/1"
          },
          "employees": {
            "href": "http://localhost:8080/employees"
          }
        }
      },
      {
        "id": 2,
        "name": "Frodo Baggins",
        "role": "thief",
        "_links": {
          "self": {
            "href": "http://localhost:8080/employees/2"
          },
          "employees": {
            "href": "http://localhost:8080/employees"
          }
        }
      }
    ]
  },
  "_links": {
    "self": {
      "href": "http://localhost:8080/employees"
    }
  }
}
```

For this aggregate root, which serves up a collection of employee resources, there is a top-level "**self**" link. The "**collection**" is listed underneath the "**_embedded**" section; this is how HAL represents collections.

And each individual member of the collection has their information as well as related links.

What is the point of adding all these links? It makes it possible to evolve REST services over time. Existing links can be maintained while new links can be added in the future. Newer clients may take advantage of the new links, while legacy clients can sustain themselves on the old links. This is especially helpful if services get relocated and moved around. As long as the link structure is maintained, clients can STILL find and interact with things.

## Simplifying Link Creation
In the code earlier, did you notice the repetition in single employee link creation? The code to provide a single link to an employee, as well as to create an "employees" link to the aggregate root, was shown twice. If that raised your concern, good! There’s a solution.

Simply put, you need to define a function that converts `Employee` objects to `EntityModel<Employee>` objects. While you could easily code this method yourself, there are benefits down the road of implementing Spring HATEOAS’s `RepresentationModelAssembler` interface—which will do the work for you.

`evolution/src/main/java/payroll/EmployeeModelAssembler.java`

```java
package payroll;

import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.*;

import org.springframework.hateoas.EntityModel;
import org.springframework.hateoas.server.RepresentationModelAssembler;
import org.springframework.stereotype.Component;

@Component
class EmployeeModelAssembler implements RepresentationModelAssembler<Employee, EntityModel<Employee>> {

  @Override
  public EntityModel<Employee> toModel(Employee employee) {

    return EntityModel.of(employee, //
        linkTo(methodOn(EmployeeController.class).one(employee.getId())).withSelfRel(),
        linkTo(methodOn(EmployeeController.class).all()).withRel("employees"));
  }
}
```

This simple interface has one method: `toModel()`. It is based on converting a non-model object (`Employee`) into a model-based object (`EntityModel<Employee>`).

All the code you saw earlier in the controller can be moved into this class. And by applying Spring Framework’s `@Component` annotation, the assembler will be automatically created when the app starts.

\* Spring HATEOAS’s abstract base class for all models is `RepresentationModel`. But for simplicity, I recommend using `EntityModel<T>` as your mechanism to easily wrap all POJOs as models.

To leverage this assembler, you only have to alter the `EmployeeController` by injecting the assembler in the constructor.

Injecting EmployeeModelAssembler into the controller

```java
@RestController
class EmployeeController {

  private final EmployeeRepository repository;

  private final EmployeeModelAssembler assembler;

  EmployeeController(EmployeeRepository repository, EmployeeModelAssembler assembler) {

    this.repository = repository;
    this.assembler = assembler;
  }

  ...

}
```

From here, you can use that assembler in the single-item employee method:

Getting single item resource using the assembler

```java
@GetMapping("/employees/{id}")
EntityModel<Employee> one(@PathVariable Long id) {

  Employee employee = repository.findById(id) //
      .orElseThrow(() -> new EmployeeNotFoundException(id));

  return assembler.toModel(employee);
}
```

This code is almost the same, except instead of creating the `EntityModel<Employee>` instance here, you delegate it to the assembler. Maybe that doesn’t look like much.

Applying the same thing in the aggregate root controller method is more impressive:

Getting aggregate root resource using the assembler

```java
@GetMapping("/employees")
CollectionModel<EntityModel<Employee>> all() {

  List<EntityModel<Employee>> employees = repository.findAll().stream() //
      .map(assembler::toModel) //
      .collect(Collectors.toList());

  return CollectionModel.of(employees, linkTo(methodOn(EmployeeController.class).all()).withSelfRel());
}
```

The code is, again, almost the same, however you get to replace all that `EntityModel<Employee>` creation logic with `map(assembler::toModel)`. Thanks to Java 8 method references, it’s super easy to plug it in and simplify your controller.

\* A key design goal of Spring HATEOAS is to make it easier to do The Right Thing™. In this scenario: adding hypermedia to your service without hard coding a thing.

At this stage, you’ve created a Spring MVC REST controller that actually produces hypermedia-powered content! Clients that don’t speak HAL can ignore the extra bits while consuming the pure data. Clients that DO speak HAL can navigate your empowered API.

But that is not the only thing needed to build a truly RESTful service with Spring.


<!--
<span class="x-understand"></span>
<span class="understand"></span>
<span class="tab"></span>
<span class="underline"></span>
<span class="cancle"></span>
<span class="green"></span>

<code class="language-plaintext highlighter-rouge"></code>

[<a id="" href="">1</a>] 참고자료1
[<a id="" href="" title="">2</a>] 참고자료2, <a href="링크" target="_blank">링크</a>
<sup><a id="" href="" target="_blank" title=""></a></sup>

<figure>
  <img src="/assets/img/category-#/#">
  <figcaption>이미지 이름</figcaption>
</figure>

<details>
  <summary>더보기</summary>
  <figure>
    <img src="/assets/img/category-#/#">
    <figcaption>이미지 이름</figcaption>
  </figure>
</details>

<details>
  <summary>더보기</summary>
  <p></p>
</details>
-->