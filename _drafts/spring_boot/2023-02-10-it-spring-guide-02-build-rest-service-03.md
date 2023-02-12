---
title: "[Spring TUTORIAL] Building REST services with Spring (3)"
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
  - [Evolving REST APIs](#evolving-rest-apis)
    - [Supporting changes to the API](#supporting-changes-to-the-api)
      - [Proper Responses](#proper-responses)
  - [Building links into your REST API](#building-links-into-your-rest-api)
  - [Summary](#summary)

\* 일부 번역기를 사용한 부분이 있음

# 관련 글 보기
- [[Spring GUIDE] Building a RESTful Web Service](https://dapin1490.github.io/satinbower/posts/it-spring-guide-01-restful-web-service/)
- [[Spring TUTORIAL] Building REST services with Spring (1)](https://dapin1490.github.io/posts/it-spring-guide-02-build-rest-service-01/)
- - [[Spring TUTORIAL] Building REST services with Spring (2)](https://dapin1490.github.io/posts/it-spring-guide-02-build-rest-service-02/)

# Building REST services with Spring
원문 보기: <https://spring.io/guides/tutorials/rest/>  
깃허브에서 보기: <https://github.com/spring-guides/tut-rest>

## Evolving REST APIs
With one additional library and a few lines of extra code, you have added hypermedia to your application. But that is not the only thing needed to make your service RESTful. An important facet of REST is the fact that it’s neither a technology stack nor a single standard.

REST is a collection of architectural constraints that when adopted make your application much more resilient. A key factor of resilience is that when you make upgrades to your services, your clients don’t suffer from downtime.

In the "olden" days, upgrades were notorious for breaking clients. In other words, an upgrade to the server required an update to the client. In this day and age, hours or even minutes of downtime spent doing an upgrade can cost millions in lost revenue.

Some companies require that you present management with a plan to minimize downtime. In the past, you could get away with upgrading at 2:00 a.m. on a Sunday when load was at a minimum. But in today’s Internet-based e-commerce with international customers in other time zones, such strategies are not as effective.

[SOAP-based services](https://www.tutorialspoint.com/soap/what_is_soap.htm) and [CORBA-based services](https://www.corba.org/faq.htm) were incredibly brittle. It was hard to roll out a server that could support both old and new clients. With REST-based practices, it’s much easier. Especially using the Spring stack.

### Supporting changes to the API
Imagine this design problem: You’ve rolled out a system with this `Employee`-based record. The system is a major hit. You’ve sold your system to countless enterprises. Suddenly, the need for an employee’s name to be split into `firstName` and `lastName` arises.

Uh oh. Didn’t think of that.

Before you open up the `Employee` class and replace the single field `name` with `firstName` and `lastName`, stop and think for a second. Will that break any clients? How long will it take to upgrade them. Do you even control all the clients accessing your services?

Downtime = lost money. Is management ready for that?

There is an old strategy that precedes REST by years.

Never delete a column in a database.  
— Unknown  
You can always add columns (fields) to a database table. But don’t take one away. The principle in RESTful services is the same.  

Add new fields to your JSON representations, but don’t take any away. Like this:

JSON that supports multiple clients

```json
{
  "id": 1,
  "firstName": "Bilbo",
  "lastName": "Baggins",
  "role": "burglar",
  "name": "Bilbo Baggins",
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

Notice how this format shows `firstName`, `lastName`, AND `name`? While it sports duplication of information, the purpose is to support both old and new clients. That means you can upgrade the server without requiring clients upgrade at the same time. A good move that should reduce downtime.

And not only should you show this information in both the "old way" and the "new way", you should also process incoming data both ways.

How? Simple. Like this:

Employee record that handles both "old" and "new" clients

```java
package payroll;

import java.util.Objects;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
class Employee {

  private @Id @GeneratedValue Long id;
  private String firstName;
  private String lastName;
  private String role;

  Employee() {}

  Employee(String firstName, String lastName, String role) {

    this.firstName = firstName;
    this.lastName = lastName;
    this.role = role;
  }

  public String getName() {
    return this.firstName + " " + this.lastName;
  }

  public void setName(String name) {
    String[] parts = name.split(" ");
    this.firstName = parts[0];
    this.lastName = parts[1];
  }

  public Long getId() {
    return this.id;
  }

  public String getFirstName() {
    return this.firstName;
  }

  public String getLastName() {
    return this.lastName;
  }

  public String getRole() {
    return this.role;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public void setFirstName(String firstName) {
    this.firstName = firstName;
  }

  public void setLastName(String lastName) {
    this.lastName = lastName;
  }

  public void setRole(String role) {
    this.role = role;
  }

  @Override
  public boolean equals(Object o) {

    if (this == o)
      return true;
    if (!(o instanceof Employee))
      return false;
    Employee employee = (Employee) o;
    return Objects.equals(this.id, employee.id) && Objects.equals(this.firstName, employee.firstName)
        && Objects.equals(this.lastName, employee.lastName) && Objects.equals(this.role, employee.role);
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.id, this.firstName, this.lastName, this.role);
  }

  @Override
  public String toString() {
    return "Employee{" + "id=" + this.id + ", firstName='" + this.firstName + '\'' + ", lastName='" + this.lastName
        + '\'' + ", role='" + this.role + '\'' + '}';
  }
}
```

This class is very similar to the previous version of `Employee`. Let’s go over the changes:

- Field `name` has been replaced by `firstName` and `lastName`.
- A "virtual" getter for the old `name` property, `getName()` is defined. It uses the `firstName` and `lastName` fields to produce a value.
- A "virtual" setter for the old `name` property is also defined, `setName()`. It parses an incoming string and stores it into the proper fields.

Of course not EVERY change to your API is as simple as splitting a string or merging two strings. But it’s surely not impossible to come up with a set of transforms for most scenarios, right?

\* Don’t forget to go and change how you preload your database (in LoadDatabase) to use this new constructor.  
```shell
log.info("Preloading " + repository.save(new Employee("Bilbo", "Baggins", "burglar")));
log.info("Preloading " + repository.save(new Employee("Frodo", "Baggins", "thief")));
```

#### Proper Responses
Another step in the right direction involves ensuring that each of your REST methods returns a proper response. Update the POST method like this:

POST that handles "old" and "new" client requests

```java
@PostMapping("/employees")
ResponseEntity<?> newEmployee(@RequestBody Employee newEmployee) {

  EntityModel<Employee> entityModel = assembler.toModel(repository.save(newEmployee));

  return ResponseEntity //
      .created(entityModel.getRequiredLink(IanaLinkRelations.SELF).toUri()) //
      .body(entityModel);
}
```

- The new `Employee` object is saved as before. But the resulting object is wrapped using the `EmployeeModelAssembler`.
- Spring MVC’s `ResponseEntity` is used to create an **HTTP 201 Created** status message. This type of response typically includes a **Location** response header, and we use the URI derived from the model’s self-related link.
- Additionally, return the model-based version of the saved object.

With these tweaks in place, you can use the same endpoint to create a new employee resource, and use the legacy `name` field:

```shell
$ curl -v -X POST localhost:8080/employees -H 'Content-Type:application/json' -d '{"name": "Samwise Gamgee", "role": "gardener"}'

# for Window
$ curl -v -X POST localhost:8080/employees -H "Content-Type:application/json" -d "{\"name\": \"Samwise Gamgee\", \"role\": \"gardener\"}"
```

The output is shown below:

```txt
> POST /employees HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
> Content-Type:application/json
> Content-Length: 46
>
< Location: http://localhost:8080/employees/3
< Content-Type: application/hal+json;charset=UTF-8
< Transfer-Encoding: chunked
< Date: Fri, 10 Aug 2018 19:44:43 GMT
<
{
  "id": 3,
  "firstName": "Samwise",
  "lastName": "Gamgee",
  "role": "gardener",
  "name": "Samwise Gamgee",
  "_links": {
    "self": {
      "href": "http://localhost:8080/employees/3"
    },
    "employees": {
      "href": "http://localhost:8080/employees"
    }
  }
}
```

This not only has the resulting object rendered in HAL (both `name` as well as `firstName`/`lastName`), but also the **Location** header populated with `http://localhost:8080/employees/3`. A hypermedia powered client could opt to "surf" to this new resource and proceed to interact with it.

The PUT controller method needs similar tweaks:

Handling a PUT for different clients

```java
@PutMapping("/employees/{id}")
ResponseEntity<?> replaceEmployee(@RequestBody Employee newEmployee, @PathVariable Long id) {

  Employee updatedEmployee = repository.findById(id) //
      .map(employee -> {
        employee.setName(newEmployee.getName());
        employee.setRole(newEmployee.getRole());
        return repository.save(employee);
      }) //
      .orElseGet(() -> {
        newEmployee.setId(id);
        return repository.save(newEmployee);
      });

  EntityModel<Employee> entityModel = assembler.toModel(updatedEmployee);

  return ResponseEntity //
      .created(entityModel.getRequiredLink(IanaLinkRelations.SELF).toUri()) //
      .body(entityModel);
}
```

The `Employee` object built from the `save()` operation is then wrapped using the `EmployeeModelAssembler` into an `EntityModel<Employee>` object. Using the `getRequiredLink()` method, you can retrieve the `Link` created by the `EmployeeModelAssembler` with a `SELF` rel. This method returns a `Link` which must be turned into a `URI` with the `toUri` method.

Since we want a more detailed HTTP response code than **200 OK**, we will use Spring MVC’s `ResponseEntity` wrapper. It has a handy static method `created()` where we can plug in the resource’s URI. It’s debatable if **HTTP 201 Created** carries the right semantics since we aren’t necessarily "creating" a new resource. But it comes pre-loaded with a **Location** response header, so run with it.

```shell
$ curl -v -X PUT localhost:8080/employees/3 -H 'Content-Type:application/json' -d '{"name": "Samwise Gamgee", "role": "ring bearer"}'

# for Window
$ curl -v -X PUT localhost:8080/employees/3 -H "Content-Type:application/json" -d "{\"name\": \"Samwise Gamgee\", \"role\": \"ring bearer\"}"
```

```txt
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> PUT /employees/3 HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
> Content-Type:application/json
> Content-Length: 49
>
< HTTP/1.1 201
< Location: http://localhost:8080/employees/3
< Content-Type: application/hal+json;charset=UTF-8
< Transfer-Encoding: chunked
< Date: Fri, 10 Aug 2018 19:52:56 GMT
{
	"id": 3,
	"firstName": "Samwise",
	"lastName": "Gamgee",
	"role": "ring bearer",
	"name": "Samwise Gamgee",
	"_links": {
		"self": {
			"href": "http://localhost:8080/employees/3"
		},
		"employees": {
			"href": "http://localhost:8080/employees"
		}
	}
}
```

That employee resource has now been updated and the location URI sent back. Finally, update the DELETE operation suitably:

Handling DELETE requests

```java
@DeleteMapping("/employees/{id}")
ResponseEntity<?> deleteEmployee(@PathVariable Long id) {

  repository.deleteById(id);

  return ResponseEntity.noContent().build();
}
```

This returns an **HTTP 204 No Content** response.

```shell
$ curl -v -X DELETE localhost:8080/employees/1
```

```txt
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> DELETE /employees/1 HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 204
< Date: Fri, 10 Aug 2018 21:30:26 GMT
```

\* Making changes to the fields in the `Employee` class will require coordination with your database team, so that they can properly migrate existing content into the new columns.

You are now ready for an upgrade that will NOT disturb existing clients while newer clients can take advantage of the enhancements!

By the way, are you worried about sending too much information over the wire? In some systems where every byte counts, evolution of APIs may need to take a backseat. But don’t pursue such premature optimization until you measure.

## Building links into your REST API
So far, you’ve built an evolvable API with bare bones links. To grow your API and better serve your clients, you need to embrace the concept of **Hypermedia as the Engine of Application State**.

What does that mean? In this section, you’ll explore it in detail.

Business logic inevitably builds up rules that involve processes. The risk of such systems is we often carry such server-side logic into clients and build up strong coupling. REST is about breaking down such connections and minimizing such coupling.

To show how to cope with state changes without triggering breaking changes in clients, imagine adding a system that fulfills orders.

As a first step, define an `Order` record:

`links/src/main/java/payroll/Order.java`

```java
package payroll;

import java.util.Objects;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "CUSTOMER_ORDER")
class Order {

  private @Id @GeneratedValue Long id;

  private String description;
  private Status status;

  Order() {}

  Order(String description, Status status) {

    this.description = description;
    this.status = status;
  }

  public Long getId() {
    return this.id;
  }

  public String getDescription() {
    return this.description;
  }

  public Status getStatus() {
    return this.status;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public void setDescription(String description) {
    this.description = description;
  }

  public void setStatus(Status status) {
    this.status = status;
  }

  @Override
  public boolean equals(Object o) {

    if (this == o)
      return true;
    if (!(o instanceof Order))
      return false;
    Order order = (Order) o;
    return Objects.equals(this.id, order.id) && Objects.equals(this.description, order.description)
        && this.status == order.status;
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.id, this.description, this.status);
  }

  @Override
  public String toString() {
    return "Order{" + "id=" + this.id + ", description='" + this.description + '\'' + ", status=" + this.status + '}';
  }
}
```

- The class requires a JPA `@Table` annotation changing the table’s name to `CUSTOMER_ORDER` because `ORDER` is not a valid name for table.
- It includes a `description` field as well as a `status` field.

Orders must go through a certain series of state transitions from the time a customer submits an order and it is either fulfilled or cancelled. This can be captured as a Java `enum`:

`links/src/main/java/payroll/Status.java`

```java
package payroll;

enum Status {

  IN_PROGRESS, //
  COMPLETED, //
  CANCELLED
}
```

This `enum` captures the various states an `Order` can occupy. For this tutorial, let’s keep it simple.

To support interacting with orders in the database, you must define a corresponding Spring Data repository:

Spring Data JPA’s `JpaRepository` base interface

```java
interface OrderRepository extends JpaRepository<Order, Long> {
}
```

With this in place, you can now define a basic `OrderController`:

`links/src/main/java/payroll/OrderController.java`

```java
@RestController
class OrderController {

  private final OrderRepository orderRepository;
  private final OrderModelAssembler assembler;

  OrderController(OrderRepository orderRepository, OrderModelAssembler assembler) {

    this.orderRepository = orderRepository;
    this.assembler = assembler;
  }

  @GetMapping("/orders")
  CollectionModel<EntityModel<Order>> all() {

    List<EntityModel<Order>> orders = orderRepository.findAll().stream() //
        .map(assembler::toModel) //
        .collect(Collectors.toList());

    return CollectionModel.of(orders, //
        linkTo(methodOn(OrderController.class).all()).withSelfRel());
  }

  @GetMapping("/orders/{id}")
  EntityModel<Order> one(@PathVariable Long id) {

    Order order = orderRepository.findById(id) //
        .orElseThrow(() -> new OrderNotFoundException(id));

    return assembler.toModel(order);
  }

  @PostMapping("/orders")
  ResponseEntity<EntityModel<Order>> newOrder(@RequestBody Order order) {

    order.setStatus(Status.IN_PROGRESS);
    Order newOrder = orderRepository.save(order);

    return ResponseEntity //
        .created(linkTo(methodOn(OrderController.class).one(newOrder.getId())).toUri()) //
        .body(assembler.toModel(newOrder));
  }
}
```

- It contains the same REST controller setup as the controllers you’ve built so far.
- It injects both an `OrderRepository` as well as a (not yet built) `OrderModelAssembler`.
- The first two Spring MVC routes handle the aggregate root as well as a single item `Order` resource request.
- The third Spring MVC route handles creating new orders, by starting them in the `IN_PROGRESS` state.
- All the controller methods return one of Spring HATEOAS’s `RepresentationModel` subclasses to properly render hypermedia (or a wrapper around such a type).

Before building the `OrderModelAssembler`, let’s discuss what needs to happen. You are modeling the flow of states between `Status.IN_PROGRESS`, `Status.COMPLETED`, and `Status.CANCELLED`. A natural thing when serving up such data to clients is to let the clients make the decision on what it can do based on this payload.

But that would be wrong.

What happens when you introduce a new state in this flow? The placement of various buttons on the UI would probably be erroneous.

What if you changed the name of each state, perhaps while coding international support and showing locale-specific text for each state? That would most likely break all the clients.

Enter **HATEOAS** or **Hypermedia as the Engine of Application State**. Instead of clients parsing the payload, give them links to signal valid actions. Decouple state-based actions from the payload of data. In other words, when **CANCEL** and **COMPLETE** are valid actions, dynamically add them to the list of links. Clients only need show users the corresponding buttons when the links exist.

This decouples clients from having to know WHEN such actions are valid, reducing the risk of the server and its clients getting out of sync on the logic of state transitions.

Having already embraced the concept of Spring HATEOAS `RepresentationModelAssembler` components, putting such logic in the `OrderModelAssembler` would be the perfect place to capture this business rule:

`links/src/main/java/payroll/OrderModelAssembler.java`

```java
package payroll;

import static org.springframework.hateoas.server.mvc.WebMvcLinkBuilder.*;

import org.springframework.hateoas.EntityModel;
import org.springframework.hateoas.server.RepresentationModelAssembler;
import org.springframework.stereotype.Component;

@Component
class OrderModelAssembler implements RepresentationModelAssembler<Order, EntityModel<Order>> {

  @Override
  public EntityModel<Order> toModel(Order order) {

    // Unconditional links to single-item resource and aggregate root

    EntityModel<Order> orderModel = EntityModel.of(order,
        linkTo(methodOn(OrderController.class).one(order.getId())).withSelfRel(),
        linkTo(methodOn(OrderController.class).all()).withRel("orders"));

    // Conditional links based on state of the order

    if (order.getStatus() == Status.IN_PROGRESS) {
      orderModel.add(linkTo(methodOn(OrderController.class).cancel(order.getId())).withRel("cancel"));
      orderModel.add(linkTo(methodOn(OrderController.class).complete(order.getId())).withRel("complete"));
    }

    return orderModel;
  }
}
```

This resource assembler always includes the **self** link to the single-item resource as well as a link back to the aggregate root. But it also includes two conditional links to `OrderController.cancel(id)` as well as `OrderController.complete(id)` (not yet defined). These links are ONLY shown when the order’s status is `Status.IN_PROGRESS`.

If clients can adopt HAL and the ability to read links instead of simply reading the data of plain old JSON, they can trade in the need for domain knowledge about the order system. This naturally reduces coupling between client and server. And it opens the door to tuning the flow of order fulfillment without breaking clients in the process.

To round out order fulfillment, add the following to the `OrderController` for the `cancel` operation:

Creating a "cancel" operation in the OrderController

```java
@DeleteMapping("/orders/{id}/cancel")
ResponseEntity<?> cancel(@PathVariable Long id) {

  Order order = orderRepository.findById(id) //
      .orElseThrow(() -> new OrderNotFoundException(id));

  if (order.getStatus() == Status.IN_PROGRESS) {
    order.setStatus(Status.CANCELLED);
    return ResponseEntity.ok(assembler.toModel(orderRepository.save(order)));
  }

  return ResponseEntity //
      .status(HttpStatus.METHOD_NOT_ALLOWED) //
      .header(HttpHeaders.CONTENT_TYPE, MediaTypes.HTTP_PROBLEM_DETAILS_JSON_VALUE) //
      .body(Problem.create() //
          .withTitle("Method not allowed") //
          .withDetail("You can't cancel an order that is in the " + order.getStatus() + " status"));
}
```

It checks the `Order` status before allowing it to be cancelled. If it’s not a valid state, it returns an [RFC-7807](https://tools.ietf.org/html/rfc7807) `Problem`, a hypermedia-supporting error container. If the transition is indeed valid, it transitions the `Order` to `CANCELLED`.

And add this to the `OrderController` as well for order completion:

Creating a "complete" operation in the OrderController

```java
@PutMapping("/orders/{id}/complete")
ResponseEntity<?> complete(@PathVariable Long id) {

  Order order = orderRepository.findById(id) //
      .orElseThrow(() -> new OrderNotFoundException(id));

  if (order.getStatus() == Status.IN_PROGRESS) {
    order.setStatus(Status.COMPLETED);
    return ResponseEntity.ok(assembler.toModel(orderRepository.save(order)));
  }

  return ResponseEntity //
      .status(HttpStatus.METHOD_NOT_ALLOWED) //
      .header(HttpHeaders.CONTENT_TYPE, MediaTypes.HTTP_PROBLEM_DETAILS_JSON_VALUE) //
      .body(Problem.create() //
          .withTitle("Method not allowed") //
          .withDetail("You can't complete an order that is in the " + order.getStatus() + " status"));
}
```

This implements similar logic to prevent an `Order` status from being completed unless in the proper state.

Let’s update `LoadDatabase` to pre-load some `Order​`s along with the `Employee`​s it was loading before.

Updating the database pre-loader

```java
package payroll;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.boot.CommandLineRunner;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;

@Configuration
class LoadDatabase {

  private static final Logger log = LoggerFactory.getLogger(LoadDatabase.class);

  @Bean
  CommandLineRunner initDatabase(EmployeeRepository employeeRepository, OrderRepository orderRepository) {

    return args -> {
      employeeRepository.save(new Employee("Bilbo", "Baggins", "burglar"));
      employeeRepository.save(new Employee("Frodo", "Baggins", "thief"));

      employeeRepository.findAll().forEach(employee -> log.info("Preloaded " + employee));

      
      orderRepository.save(new Order("MacBook Pro", Status.COMPLETED));
      orderRepository.save(new Order("iPhone", Status.IN_PROGRESS));

      orderRepository.findAll().forEach(order -> {
        log.info("Preloaded " + order);
      });
      
    };
  }
}
```

Now you can test things out!

To use the newly minted order service, just perform a few operations:

```shell
$ curl -v http://localhost:8080/orders
```

```txt
{
  "_embedded": {
    "orderList": [
      {
        "id": 3,
        "description": "MacBook Pro",
        "status": "COMPLETED",
        "_links": {
          "self": {
            "href": "http://localhost:8080/orders/3"
          },
          "orders": {
            "href": "http://localhost:8080/orders"
          }
        }
      },
      {
        "id": 4,
        "description": "iPhone",
        "status": "IN_PROGRESS",
        "_links": {
          "self": {
            "href": "http://localhost:8080/orders/4"
          },
          "orders": {
            "href": "http://localhost:8080/orders"
          },
          "cancel": {
            "href": "http://localhost:8080/orders/4/cancel"
          },
          "complete": {
            "href": "http://localhost:8080/orders/4/complete"
          }
        }
      }
    ]
  },
  "_links": {
    "self": {
      "href": "http://localhost:8080/orders"
    }
  }
}
```

This HAL document immediately shows different links for each order, based upon its present state.

- The first order, being **COMPLETED** only has the navigational links. The state transition links are not shown.
- The second order, being **IN_PROGRESS** additionally has the **cancel** link as well as the **complete** link.

Try cancelling an order:

```shell
$ curl -v -X DELETE http://localhost:8080/orders/4/cancel
```

```txt
> DELETE /orders/4/cancel HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 200
< Content-Type: application/hal+json;charset=UTF-8
< Transfer-Encoding: chunked
< Date: Mon, 27 Aug 2018 15:02:10 GMT
<
{
  "id": 4,
  "description": "iPhone",
  "status": "CANCELLED",
  "_links": {
    "self": {
      "href": "http://localhost:8080/orders/4"
    },
    "orders": {
      "href": "http://localhost:8080/orders"
    }
  }
}
```

This response shows an **HTTP 200** status code indicating it was successful. The response HAL document shows that order in its new state (`CANCELLED`). And the state-altering links gone.

If you try the same operation again...

```shell
$ curl -v -X DELETE http://localhost:8080/orders/4/cancel
```

```txt
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> DELETE /orders/4/cancel HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 405
< Content-Type: application/problem+json
< Transfer-Encoding: chunked
< Date: Mon, 27 Aug 2018 15:03:24 GMT
<
{
  "title": "Method not allowed",
  "detail": "You can't cancel an order that is in the CANCELLED status"
}
```

...you see an **HTTP 405 Method Not Allowed** response. **DELETE** has become an invalid operation. The `Problem` response object clearly indicates that you aren’t allowed to "cancel" an order already in the "CANCELLED" status.

Additionally, trying to complete the same order also fails:

```shell
$ curl -v -X PUT localhost:8080/orders/4/complete
```

```txt
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> PUT /orders/4/complete HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 405
< Content-Type: application/problem+json
< Transfer-Encoding: chunked
< Date: Mon, 27 Aug 2018 15:05:40 GMT
<
{
  "title": "Method not allowed",
  "detail": "You can't complete an order that is in the CANCELLED status"
}
```

With all this in place, your order fulfillment service is capable of conditionally showing what operations are available. It also guards against invalid operations.

By leveraging the protocol of hypermedia and links, clients can be built sturdier and less likely to break simply because of a change in the data. And Spring HATEOAS eases building the hypermedia you need to serve to your clients.

## Summary
Throughout this tutorial, you have engaged in various tactics to build REST APIs. As it turns out, REST isn’t just about pretty URIs and returning JSON instead of XML.

Instead, the following tactics help make your services less likely to break existing clients you may or may not control:

- Don’t remove old fields. Instead, support them.
- Use rel-based links so clients don’t have to hard code URIs.
- Retain old links as long as possible. Even if you have to change the URI, keep the rels so older clients have a path onto the newer features.
- Use links, not payload data, to instruct clients when various state-driving operations are available.

It may appear to be a bit of effort to build up `RepresentationModelAssembler` implementations for each resource type and to use these components in all of your controllers. But this extra bit of server-side setup (made easy thanks to Spring HATEOAS) can ensure the clients you control (and more importantly, those you don’t) can upgrade with ease as you evolve your API.

This concludes our tutorial on how to build RESTful services using Spring. Each section of this tutorial is managed as a separate subproject in a single github repo:

- **nonrest** — Simple Spring MVC app with no hypermedia
- **rest** — Spring MVC + Spring HATEOAS app with HAL representations of each resource
- **evolution** — REST app where a field is evolved but old data is retained for backward compatibility
- **links** — REST app where conditional links are used to signal valid state changes to clients

To view more examples of using Spring HATEOAS see <https://github.com/spring-projects/spring-hateoas-examples>.

To do some more exploring check out the following video by Spring teammate Oliver Gierke:

<iframe width="300" height="150" src="https://www.youtube.com/embed/WDBUlu_lYas" title="REST Beyond the Obvious - API Design for Ever-Evolving Systems" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

Want to write a new guide or contribute to an existing one? Check out our [contribution guidelines](https://github.com/spring-guides/getting-started-guides/wiki).

\* All guides are released with an ASLv2 license for the code, and an [Attribution, NoDerivatives creative commons license](http://creativecommons.org/licenses/by-nd/3.0/) for the writing.

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