---
title: "[Spring TUTORIAL] Building REST services with Spring (1)"
author: dapin1490
date: 2023-02-10T00:09:00+09:00
categories: [IT, Spring Boot]
tags: [지식, IT, Spring, Spring Boot, Gradle, Tutorial]
render_with_liquid: false
---

## Table of Contents
- [관련 글 보기](#관련-글-보기)
- [Building REST services with Spring](#building-rest-services-with-spring)
  - [Getting Started](#getting-started)
  - [The Story so Far...](#the-story-so-far)
  - [HTTP is the Platform](#http-is-the-platform)

\* 일부 번역기를 사용한 부분이 있음

# 관련 글 보기
- [[Spring GUIDE] Building a RESTful Web Service](https://dapin1490.github.io/satinbower/posts/it-spring-guide-01-restful-web-service/)

# Building REST services with Spring
원문 보기: <https://spring.io/guides/tutorials/rest/>  
깃허브에서 보기: <https://github.com/spring-guides/tut-rest>  

REST는 구축하기 쉽고 사용하기 쉽기 때문에 웹에서 웹 서비스를 구축하는 사실상의<sup>de-facto</sup> 표준이 되었다.  

마이크로서비스의 세계에서 REST가 어떻게 적합한지에 대해서는 훨씬 더 많은 논의가 필요하지만, 이 자습서에서는 RESTful 서비스 구축에 대해서만 살펴보기로 한다.  

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

중요한 것은 REST가 아무리 유비쿼터스일지라도 그 자체가 표준이 아니라 웹 스케일 시스템을 구축하는 데 도움이 될 수 있는 접근 방식, 스타일, 아키텍처의 제약 조건 집합이라는 것이다. 이 자습서에서는 스프링 포트폴리오를 사용하여 REST의 스택리스 기능을 활용하면서 RESTful 서비스를 구축할 것이다.

## Getting Started
이 자습서는 [Spring Boot](https://spring.io/projects/spring-boot)를 사용한다. [Spring Initializr](https://start.spring.io/)로 이동하여 프로젝트에 다음 종속성을 추가한다.

- Web
- JPA
- H2

이름을 "Payroll"로 변경한 후 "Generate Project"를 선택하고 `.zip`이 다운로드된다. 압축을 푼다. 내부에는 `pom.xml` 빌드 파일을 포함한 Maven 기반의 간단한 프로젝트가 있다(참고: Gradle을 *사용할 수 있다*. 이 자습서의 예는 Maven 기반이다.)

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

\* JPA 외에도 여러 개의 repository 구현이 있다. Spring Data MongoDB, Spring Data GemFire, Spring Data Cassandra 등을 사용할 수 있다. 이 자습서는 JPA로 진행한다.

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

`@SpringBootApplication`은 **구성 요소 검색**, **자동 구성**, **속성 지원**을 적용하는 메타 주석<sup>meta-annotation</sup>이다. 이 자습서에서는 Spring Boot에 대한 자세한 내용을 자세히 설명하지는 않겠지만 본질적으로 서블릿 컨테이너<sup>servlet container</sup>가 작동하고 서비스가 제공된다.

그래도 데이터가 없는 애플리케이션은 별로 흥미롭지 않으니 미리 로드해보자. 다음 클래스는 Spring에 의해 자동으로 로드된다:

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

로드할 때 무슨 일이 일어날까?

- 일단 애플리케이션의 context가 로드되면 Spring Boot가 모든 `CommandLineRunner` bean을 실행할 것이다.
- 이 실행자<sup>runner</sup>는 당신이 방금 만든 `EmployeeRepository`의 사본을 요청할 것이다.
- 이를 이용해, 그것은 두 객체<sup>entities</sup>를 만들고 저장한다.

우클릭을 하고 `PayRollApplication`을 **실행하면** 다음과 같은 결과를 얻을 수 있다:

데이터를 미리 로드하는 중 보이는 콘솔 출력문의 일부이다.

```txt
...
2018-08-09 11:36:26.169  INFO 74611 --- [main] payroll.LoadDatabase : Preloading Employee(id=1, name=Bilbo Baggins, role=burglar)
2018-08-09 11:36:26.174  INFO 74611 --- [main] payroll.LoadDatabase : Preloading Employee(id=2, name=Frodo Baggins, role=thief)
...
```

이것은 **전체** 로그가 아니라 데이터 사전 로드의 주요 부분일 뿐이다. (실제로 전체 콘솔을 확인하라. 멋질 것이다.)

## HTTP is the Platform
웹 계층으로 repository를 감싸려면 Spring MVC로 전환해야 한다. Spring Boot 덕분에 코딩할 인프라가 거의 없다. 대신, 우리는 다음과 같은 조치에 집중할 수 있다:

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

- `@RestController`는 각 메서드에서 반환되는 데이터가 템플릿을 렌더링하는 대신 응답 본문에 직접 기록됨을 나타낸다.
- `EmployeeRepository`는 생성자에 의해 컨트롤러에 주입된다<sup>injected</sup>.
- 각 작업(HTTP `GET`, `POST`, `PUT`, `DELETE` 호출에 해당하는 `@GetMapping`, `@PostMapping`, `@PutMapping`, `@DeleteMapping`)에 대한 경로가 있다. (참고: 각 방법을 읽고 그것이 무엇을 하는지 이해하는 것이 유용하다.)
- `EmployeeNotFoundException`은 직원을 조회했지만 찾을 수 없는 경우를 나타내는 예외이다.

`nonrest/src/main/java/payroll/EmployeeNotFoundException.java`

```java
package payroll;

class EmployeeNotFoundException extends RuntimeException {

  EmployeeNotFoundException(Long id) {
    super("Could not find employee " + id);
  }
}
```

`EmployeeNotFoundException`이 발생하면, 다음 Spring MVC 구성의 추가 tidbit이 **HTTP 404**를 렌더링하는 데 사용된다:

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

- `@ResponseBody`는 이 조언<sup>advice</sup>이 응답 본문으로 바로 렌더링된다는 신호를 보낸다.
- `@ExceptionHandler`는 `EmployeeNotFoundException`이 발생했을 때만 응답하도록 조언<sup>advice</sup>을 구성한다.
- `@ResponseStatus`는 `HttpStatus.NOT_FOUND`, 즉 **HTTP 404**를 발행<sup>issue</sup>하도록 지시한다.
- 조언<sup>advice</sup>의 본문은 콘텐츠를 생성한다. 이 경우 예외에 대한 메시지를 제공한다.

애플리케이션을 시작하려면 `PayRollApplication`에서 `public static void main`을 마우스 오른쪽 버튼으로 클릭하고 IDE에서 **실행**을 선택하거나, 아래와 같이 시도할 수 있다.

Spring Initializr는 maven wrapper를 사용하므로 다음과 같이 입력한다:

```shell
$ ./mvnw clean spring-boot:run
```

또는 설치된 maven 버전을 사용하여 다음과 같이 입력한다:

```shell
$ mvn clean spring-boot:run
```

앱이 시작되면 즉시 질의할<sup>interrogate</sup> 수 있다.

```shell
$ curl -v localhost:8080/employees
```

결과는 다음과 같을 것이다:

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

여기에서 미리 로드된 데이터를 압축된 형식으로 볼 수 있다.

존재하지 않는 사용자를 쿼리하려고 하면...

```shell
$ curl -v localhost:8080/employees/99
```

결과는...

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

이 메시지는 **employee 99를 찾을 수 없습니다**라는 사용자 지정 메시지와 함께 **HTTP 404** 오류를 멋지게 표시한다.

현재 코딩된 상호작용을 보여주는 것은 어렵지 않다...

\* Windows 명령 프롬프트를 사용하여 cURL 명령을 실행하는 경우 아래 명령이 제대로 작동하지 않을 수 있다. 작은따옴표로 묶인 인수를 지원하는 터미널을 선택하거나 큰따옴표를 사용한 다음 JSON 내부의 인수를 이스케이프 처리해야 한다.

터미널에서 다음 명령을 사용하여 새 `Employee` 레코드를 생성한다. 시작 부분의 `$`는 그 뒤에 오는 명령이 터미널 명령임을 나타낸다:

```shell
$ curl -X POST localhost:8080/employees -H 'Content-type:application/json' -d '{"name": "Samwise Gamgee", "role": "gardener"}'

# for Window
$ curl -X POST localhost:8080/employees -H "Content-type:application/json" -d "{\"name\": \"Samwise Gamgee\", \"role\": \"gardener\"}"
```

그런 다음 새로 생성된 직원을 저장하고 우리에게 다시 보낸다:

```txt
{"id":3,"name":"Samwise Gamgee","role":"gardener"}
```

사용자를 업데이트할 수 있다. 그의 역할을 변경해 보겠다.

```shell
$ curl -X PUT localhost:8080/employees/3 -H 'Content-type:application/json' -d '{"name": "Samwise Gamgee", "role": "ring bearer"}'

# for Window
$ curl -X PUT localhost:8080/employees/3 -H "Content-type:application/json" -d "{\"name\": \"Samwise Gamgee\", \"role\": \"ring bearer\"}"
```

그리고 출력에 반영된 변경 사항을 확인할 수 있다.

```txt
{"id":3,"name":"Samwise Gamgee","role":"ring bearer"}
```

\* 서비스를 구성하는 방식은 상당한 영향력을 갖는다. 이 상황에서는 **업데이트**라고 했지만 **교체**라고 하는 것이 더 나은 설명이다. 예를 들어, 이름이 제공되지 *않으면* 대신 무효화된다<sup>nulled out</sup>.

마지막으로 다음과 같이 사용자를 삭제할 수 있다:

```shell
$ curl -X DELETE localhost:8080/employees/3

# Now if we look again, it's gone
# 다시 검색하면 사라져있다
$ curl localhost:8080/employees/3
Could not find employee 3
```

다 좋은데, RESTful 서비스는 아직인가? (잘 모르겠다면, 대답은 '아직이다'이다.)

뭐가 빠졌을까?

이후의 내용은 다음 글에서 확인해보자. 분량이 너무 길어서 몇 개의 글로 나누어 올릴 생각이다.