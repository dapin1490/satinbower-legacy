---
title: "[Spring TUTORIAL] Building REST services with Spring"
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
  - [Getting Started](#getting-started)
  - [The Story so Far...](#the-story-so-far)
  - [HTTP is the Platform](#http-is-the-platform)
  - [What makes something RESTful?](#what-makes-something-restful)
  - [Simplifying Link Creation](#simplifying-link-creation)
  - [Evolving REST APIs](#evolving-rest-apis)
  - [Building links into your REST API](#building-links-into-your-rest-api)
  - [Summary](#summary)

\* 일부 번역기를 사용한 부분이 있음

# 관련 글 보기
- [[Spring GUIDE] Building a RESTful Web Service](https://dapin1490.github.io/satinbower/posts/it-spring-guide-01-restful-web-service/)

# Building REST services with Spring
원문 보기: <https://spring.io/guides/tutorials/rest/>  
깃허브에서 보기: <https://github.com/spring-guides/tut-rest>

REST는 구축하기 쉽고 사용하기 쉽기 때문에 웹에서 웹 서비스를 구축하는 실질적인<sup>de-facto</sup> 표준이 되었다.  

마이크로서비스 분야에서 REST가 어떻게 적합한지에 대해 훨씬 더 많은 논의가 필요하지만, 이 튜토리얼에서는 RESTful 서비스 구축에 대해 살펴보겠다.  

왜 REST일까? REST는 아키텍처, 이점<sup>benefits</sup> 및 기타 모든 것을 포함하여 웹의 수칙<sup>the precepts of the web</sup>을 수용한다. 이는 저자 Roy Fielding이 웹이 작동하는 방식을 지배하는 십여 가지 사양<sup>specs</sup>에 관여했다는 점을 고려하면 놀라운 일이 아니다.  

무엇이 이득이었을까? 웹과 그것의 핵심 프로토콜인 HTTP는 다음과 같은 기능을 제공한다.

- 적절한 동작 (`GET`, `POST`, `PUT`, `DELETE`, ...​)
- 캐싱
- 리다이렉션과 포워딩
- 보안 (암호화 및 인증)

이들은 탄력적인 서비스를 만드는 데 중요한 요소들이다. 그러나 이게 다가 아니다. 웹은 많은 작은 사양<sup>specs</sup>으로 만들어졌기 때문에 "표준 전쟁"<i>(원문은 standards wars, 스타 워즈의 말장난)</i>에 갇히지 않고 쉽게 진화할 수 있었다.  

개발자들은 이러한 다양한 사양을 구현하는 서드 파티 툴킷을 활용할 수 있으며 클라이언트 및 서버 기술을 즉시 사용할 수 있다.  

HTTP 위에 구축함으로써, REST API는 다음을 구축할 수 있는 수단을 제공한다.

- 이전 버전과 호환되는 API
- 진화 가능한 API
- 확장 가능한 서비스
- 보안 서비스
- 상태 비저장 서비스부터 상태 저장 서비스까지

중요한 것은 REST가 아무리 유비쿼터스일지라도 그 자체가 표준이 아니라 웹 스케일 시스템을 구축하는 데 도움이 될 수 있는 접근 방식, 스타일, 아키텍처의 제약 조건 집합이라는 것이다. 이 튜토리얼에서는 스프링 포트폴리오를 사용하여 REST의 스택리스 기능을 활용하면서 RESTful 서비스를 구축할 것이다.

## Getting Started
이 튜토리얼은 [Spring Boot](https://spring.io/projects/spring-boot)를 사용한다. [Spring Initializr](https://start.spring.io/)로 이동하여 프로젝트에 다음 종속성을 추가한다.

- Web
- JPA
- H2

이름을 "Payroll"로 변경한 후 "Generate Project"를 선택하고 `.zip`이 다운로드된다. 압축을 푼다. 내부에는 `pom.xml` 빌드 파일을 포함한 Maven 기반의 간단한 프로젝트가 있다(참고: Gradle을 *사용할 수 있다*. 이 튜토리얼의 예는 Maven 기반이다.)

Spring Boot는 모든 IDE와 함께 작동할 수 있다. Eclipse, IntelliJ IDEA, Netbeans 등을 사용할 수 있다. [Spring Tool Suite](https://spring.io/tools/)(STS)는 이클립스의 Java EE 배포판의 상위 집합을 제공하는 오픈 소스 Eclipse 기반 IDE 배포판이다. Spring 애플리케이션을 훨씬 더 쉽게 사용할 수 있는 기능이 포함되어 있지만 STS가 필수는 아니다. 하지만 키 입력을 위한 추가 **공간<sup>oomph</sup>**을 원한다면 고려해 보라. 다음은 STS와 Spring Boot를 시작하는 방법을 보여주는 비디오이다. 이것은 도구에 익숙해지기 위한 일반적인 소개이다.

<iframe width="300" height="150" src="https://www.youtube.com/embed/p8AdyMlpmPk" title="Spring Boot and Spring Tool Suite" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## The Story so Far...
우리가 구성할 수 있는 가장 간단한 것부터 시작한다. 사실, 가능한 한 간단하게 하기 위해서 REST의 개념을 생략할 수도 있다. (나중에 REST를 추가하여 차이점을 이해할 것이다.)

개요<sup>Big picture</sup>: 회사의 직원들을 관리하는 간단한 급여 서비스를 만들 것이다. 직원 개체를 메모리 내 H2 데이터베이스에 저장하고 JPA라고 불리는 것을 통해 액세스한다. 그런 다음 인터넷을 통해 액세스할 수 있는 기능(Spring MVC 계층이라고 함)으로 포장한다.

다음 코드는 시스템에서 직원을 정의한다.
`nonrest/src/main/java/payroll/Employee.java`

```java
package payroll;

import java.util.Objects;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.Id;

@Entity
class Employee {

  private @Id @GeneratedValue Long id;
  private String name;
  private String role;

  Employee() {}

  Employee(String name, String role) {

    this.name = name;
    this.role = role;
  }

  public Long getId() {
    return this.id;
  }

  public String getName() {
    return this.name;
  }

  public String getRole() {
    return this.role;
  }

  public void setId(Long id) {
    this.id = id;
  }

  public void setName(String name) {
    this.name = name;
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
    return Objects.equals(this.id, employee.id) && Objects.equals(this.name, employee.name)
        && Objects.equals(this.role, employee.role);
  }

  @Override
  public int hashCode() {
    return Objects.hash(this.id, this.name, this.role);
  }

  @Override
  public String toString() {
    return "Employee{" + "id=" + this.id + ", name='" + this.name + '\'' + ", role='" + this.role + '\'' + '}';
  }
}
```

이 자바 클래스는 작지만 많은 것을 포함한다.

- `@Entity`는 이 객체를 JPA 기반 데이터 저장소에 저장할 수 있도록 하는 JPA 주석이다.
- `id`, `name`, `role`은 Employee [도메인 객체](https://www.google.com/search?q=what+is+a+domain+object+in+java)의 속성이다. `id`는 기본 키임을 나타내기 위해 더 많은 JPA 주석으로 표시되며 JPA 제공자에 의해 자동으로 채워진다.
- 사용자 지정 생성자는 새 인스턴스를 만들어야 하지만 아직 ID가 없을 때 생성된다. *(코드를 보건대, `name`과 `role`은 있지만 `id`가 없는 인스턴스를 만들 때 사용자 지정 생성자를 사용한다는 뜻인 것 같다.)*

이 도메인 객체 정의를 통해, 이제 [Spring Data JPA](https://spring.io/guides/gs/accessing-data-jpa/)로 전환하여 지루한 데이터베이스 상호 작용을 처리할 수 있다.

Spring Data JPA repository는 백엔드 데이터 저장소에 대한 레코드 생성, 읽기, 업데이트, 삭제를 지원하는 메서드를 갖는 인터페이스이다. 일부 repository는 적절한 경우 데이터 페이징과 정렬도 지원한다. Spring Data는 인터페이스의 메서드 명명에서 발견된 규칙을 기반으로 구현<sup>implementation</sup>을 합성한다<sup>synthesize</sup>.

\* JPA 외에도 여러 개의 repository 구현이 있다. Spring Data MongoDB, Spring Data GemFire, Spring Data Cassandra 등을 사용할 수 있다. 이 튜토리얼은 JPA로 진행한다.

Spring을 사용하면 데이터에 쉽게 액세스할 수 있다. 다음과 같은 `EmployeeRepository` 인터페이스를 선언하기만 하면 자동으로 다음과 같은 것들이 가능해진다:

- 새 Employee 생성
- 이미 있는 기록 업데이트
- Employee 삭제
- Employee 검색 (하나, 전부, 간단한 검색, 복잡한 속성 검색)

`nonrest/src/main/java/payroll/EmployeeRepository.java`

```java
package payroll;

import org.springframework.data.jpa.repository.JpaRepository;

interface EmployeeRepository extends JpaRepository<Employee, Long> {

}
```

이 모든 무료 기능을 얻으려면 Spring Data JPA의 `JpaRepository`를 상속<sup>extends</sup>하는 인터페이스를 선언하고 도메인 유형을 `Employee`, ID 유형을 `Long`으로 지정하기만 하면 된다.

Spring Data의 [repository solution](https://docs.spring.io/spring-data/jpa/docs/current/reference/html/#repositories)을 사용하면 데이터 저장소 세부 사항을 생략하고 대신 도메인별 용어를 사용하여 대부분의 문제를 해결할 수 있다.

믿거나 말거나, 여기까지만 해도 애플리케이션을 실행하기에 충분하다! Spring Boot 응용 프로그램은 최소한 `public static void main` 엔트리 포인트와 `@SpringBootApplication` 주석만 있으면 된다. 이것은 Spring Boot가 될 수 있는 대로 도움이 되게 한다. *(주: 이 부분을 어떻게 번역해야 할지 영 감이 안 잡혀서 원문을 남겨둠)*  
Believe it or not, this is enough to launch an application! A Spring Boot application is, at a minimum, a `public static void main` entry-point and the `@SpringBootApplication` annotation. This tells Spring Boot to help out, wherever possible.

`nonrest/src/main/java/payroll/PayrollApplication.java`

```java
package payroll;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class PayrollApplication {

  public static void main(String... args) {
    SpringApplication.run(PayrollApplication.class, args);
  }
}
```

`@SpringBootApplication` is a meta-annotation that pulls in **component scanning**, **autoconfiguration**, and **property support**. We won’t dive into the details of Spring Boot in this tutorial, but in essence, it will fire up a servlet container and serve up our service.

Nevertheless, an application with no data isn’t very interesting, so let’s preload it. The following class will get loaded automatically by Spring:

`nonrest/src/main/java/payroll/LoadDatabase.java`

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
  CommandLineRunner initDatabase(EmployeeRepository repository) {

    return args -> {
      log.info("Preloading " + repository.save(new Employee("Bilbo Baggins", "burglar")));
      log.info("Preloading " + repository.save(new Employee("Frodo Baggins", "thief")));
    };
  }
}
```

What happens when it gets loaded?

- Spring Boot will run ALL `CommandLineRunner` beans once the application context is loaded.
- This runner will request a copy of the `EmployeeRepository` you just created.
- Using it, it will create two entities and store them.

Right-click and **Run** `PayRollApplication`, and this is what you get:

Fragment of console output showing preloading of data

```txt
...
2018-08-09 11:36:26.169  INFO 74611 --- [main] payroll.LoadDatabase : Preloading Employee(id=1, name=Bilbo Baggins, role=burglar)
2018-08-09 11:36:26.174  INFO 74611 --- [main] payroll.LoadDatabase : Preloading Employee(id=2, name=Frodo Baggins, role=thief)
...
```

This isn’t the **whole** log, but just the key bits of preloading data. (Indeed, check out the whole console. It’s glorious.)

## HTTP is the Platform
To wrap your repository with a web layer, you must turn to Spring MVC. Thanks to Spring Boot, there is little in infrastructure to code. Instead, we can focus on actions:

`nonrest/src/main/java/payroll/EmployeeController.java`

```java
package payroll;

import java.util.List;

import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.PutMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RestController;

@RestController
class EmployeeController {

  private final EmployeeRepository repository;

  EmployeeController(EmployeeRepository repository) {
    this.repository = repository;
  }


  // Aggregate root
  // tag::get-aggregate-root[]
  @GetMapping("/employees")
  List<Employee> all() {
    return repository.findAll();
  }
  // end::get-aggregate-root[]

  @PostMapping("/employees")
  Employee newEmployee(@RequestBody Employee newEmployee) {
    return repository.save(newEmployee);
  }

  // Single item
  
  @GetMapping("/employees/{id}")
  Employee one(@PathVariable Long id) {
    
    return repository.findById(id)
      .orElseThrow(() -> new EmployeeNotFoundException(id));
  }

  @PutMapping("/employees/{id}")
  Employee replaceEmployee(@RequestBody Employee newEmployee, @PathVariable Long id) {
    
    return repository.findById(id)
      .map(employee -> {
        employee.setName(newEmployee.getName());
        employee.setRole(newEmployee.getRole());
        return repository.save(employee);
      })
      .orElseGet(() -> {
        newEmployee.setId(id);
        return repository.save(newEmployee);
      });
  }

  @DeleteMapping("/employees/{id}")
  void deleteEmployee(@PathVariable Long id) {
    repository.deleteById(id);
  }
}
```

- `@RestController` indicates that the data returned by each method will be written straight into the response body instead of rendering a template.
- An `EmployeeRepository` is injected by constructor into the controller.
- We have routes for each operation (`@GetMapping`, `@PostMapping`, `@PutMapping` and `@DeleteMapping`, corresponding to HTTP `GET`, `POST`, `PUT`, and `DELETE` calls). (NOTE: It’s useful to read each method and understand what they do.)
- `EmployeeNotFoundException` is an exception used to indicate when an employee is looked up but not found.

`nonrest/src/main/java/payroll/EmployeeNotFoundException.java`

```java
package payroll;

class EmployeeNotFoundException extends RuntimeException {

  EmployeeNotFoundException(Long id) {
    super("Could not find employee " + id);
  }
}
```

When an `EmployeeNotFoundException` is thrown, this extra tidbit of Spring MVC configuration is used to render an **HTTP 404**:

`nonrest/src/main/java/payroll/EmployeeNotFoundAdvice.java`

```java
package payroll;

import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.ControllerAdvice;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;

@ControllerAdvice
class EmployeeNotFoundAdvice {

  @ResponseBody
  @ExceptionHandler(EmployeeNotFoundException.class)
  @ResponseStatus(HttpStatus.NOT_FOUND)
  String employeeNotFoundHandler(EmployeeNotFoundException ex) {
    return ex.getMessage();
  }
}
```

- `@ResponseBody` signals that this advice is rendered straight into the response body.
- `@ExceptionHandler` configures the advice to only respond if an `EmployeeNotFoundException` is thrown.
- `@ResponseStatus` says to issue an `HttpStatus.NOT_FOUND`, i.e. an **HTTP 404**.
- The body of the advice generates the content. In this case, it gives the message of the exception.

To launch the application, either right-click the `public static void main` in `PayRollApplication` and select **Run** from your IDE, or:

Spring Initializr uses maven wrapper so type this:

```shell
$ ./mvnw clean spring-boot:run
```

Alternatively using your installed maven version type this:

```shell
$ mvn clean spring-boot:run
```

When the app starts, we can immediately interrogate it.

```shell
$ curl -v localhost:8080/employees
```

This will yield:

```txt
*   Trying ::1...
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> GET /employees HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 200
< Content-Type: application/json;charset=UTF-8
< Transfer-Encoding: chunked
< Date: Thu, 09 Aug 2018 17:58:00 GMT
<
* Connection #0 to host localhost left intact
[{"id":1,"name":"Bilbo Baggins","role":"burglar"},{"id":2,"name":"Frodo Baggins","role":"thief"}]
```

Here you can see the pre-loaded data, in a compacted format.

If you try and query a user that doesn’t exist...

```shell
$ curl -v localhost:8080/employees/99
```

You get...

```txt
*   Trying ::1...
* TCP_NODELAY set
* Connected to localhost (::1) port 8080 (#0)
> GET /employees/99 HTTP/1.1
> Host: localhost:8080
> User-Agent: curl/7.54.0
> Accept: */*
>
< HTTP/1.1 404
< Content-Type: text/plain;charset=UTF-8
< Content-Length: 26
< Date: Thu, 09 Aug 2018 18:00:56 GMT
<
* Connection #0 to host localhost left intact
Could not find employee 99
```

This message nicely shows an **HTTP 404** error with the custom message **Could not find employee 99**.

It's not hard to show the currently coded interactions...

\* If you are using Windows Command Prompt to issue cURL commands, chances are the below command won’t work properly. You must either pick a terminal that support single quoted arguments, or use double quotes and then escape the ones inside the JSON.

To create a new `Employee` record we use the following command in a terminal—the `$` at the beginning signifies that what follows it is a terminal command:

```shell
$ curl -X POST localhost:8080/employees -H 'Content-type:application/json' -d '{"name": "Samwise Gamgee", "role": "gardener"}'
```

Then it stores newly created employee and sends it back to us:

```txt
{"id":3,"name":"Samwise Gamgee","role":"gardener"}
```

You can update the user. Let’s change his role.

```shell
$ curl -X PUT localhost:8080/employees/3 -H 'Content-type:application/json' -d '{"name": "Samwise Gamgee", "role": "ring bearer"}'
```

And we can see the change reflected in the output.

```txt
{"id":3,"name":"Samwise Gamgee","role":"ring bearer"}
```

\* The way you construct your service can have significant impacts. In this situation, we said **update**, but **replace** is a better description. For example, if the name was NOT provided, it would instead get nulled out.

Finally, you can delete users like this:

```shell
$ curl -X DELETE localhost:8080/employees/3

# Now if we look again, it's gone
$ curl localhost:8080/employees/3
Could not find employee 3
```

This is all well and good, but do we have a RESTful service yet? (If you didn’t catch the hint, the answer is no.)

What’s missing?

## What makes something RESTful?


## Simplifying Link Creation


## Evolving REST APIs


## Building links into your REST API


## Summary


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