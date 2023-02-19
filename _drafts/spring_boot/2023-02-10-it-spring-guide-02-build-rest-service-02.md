---
title: "[Spring TUTORIAL] Building REST services with Spring (2)"
author: dapin1490
date: 2023-02-19T17:33:00+09:00
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
지금까지는 직원 데이터와 관련된 핵심 작업을 처리하는 웹 기반 서비스를 만들었다. 하지만 이것만으로는 "RESTful"을 구현하기에 충분하지 않다.

- `/employees/3`과 같은 예쁜 URL은 REST가 아니다.
- 단순히 `GET`, `POST` 등을 사용하는 것은 REST가 아니다.
- 모든 CRUD 작업이 배치되어 있는 것이 REST는 아니다.

사실 지금까지 구축한 것은 **RPC**(**원격 프로시저 호출**)로 더 잘 설명할 수 있다. 왜냐하면 이 서비스와 상호 작용하는 방법을 알 수 있는 방법이 없기 때문이다. 만약 오늘 이 내용을 공개한다면, 모든 세부 사항이 담긴 문서를 작성하거나 개발자 포털을 어딘가에 호스팅해야 할 것이다.

Roy Fielding의 이 말<sup>statement</sup>은 **REST**와 **RPC**의 차이점에 대한 실마리를 제공할 수 있다:

HTTP 기반 인터페이스를 REST API라고 부르는 사람들이 너무 많아서 답답합니다. 오늘의 예는 SocialSite REST API입니다. 바로 RPC입니다. RPC라고 외칩니다. 너무 많은 커플링이 표시되어 있어 X 등급을 부여해야 합니다(원문: There is so much coupling on display that it should be given an X rating).

하이퍼텍스트가 제약 조건이라는 개념에 대해 REST 아키텍처 스타일을 명확히 하려면 어떻게 해야 할까요? 다시 말해, 애플리케이션 상태 엔진(따라서 API)이 하이퍼텍스트에 의해 구동되지 않는다면 RESTful이 될 수 없으며 REST API가 될 수 없습니다. 끝입니다<sup>Period</sup>. 어딘가에 수정해야 할 잘못된 매뉴얼이 있나요?

— Roy Fielding  
<i><a href="https://roy.gbiv.com/untangled/2008/rest-apis-must-be-hypertext-driven">https://roy.gbiv.com/untangled/2008/rest-apis-must-be-hypertext-driven</a></i>

하이퍼미디어<sup>hypermedia</sup>를 표현<sup>representations</sup>에 포함하지 않을 경우의 부작용은 클라이언트가 API를 탐색하기 위해 URI를 하드 코딩해야 한다는 것이다. 이는 웹에서 e-commerce가 등장하기 전과 같은 취약한 특성으로 이어진다. 이는 JSON 출력에 약간의 도움이 필요하다는 신호이다.

하이퍼미디어 기반 출력물을 작성할 수 있도록 도와주는 Spring 프로젝트인 [Spring HATEOAS](https://spring.io/projects/spring-hateoas)를 소개한다. 서비스를 RESTful로 업그레이드하려면 빌드에 추가하라:

[ `pom.xml`의 `dependencies` 섹션에 Spring HATEOAS 추가하기 ]

```xml
<dependency>
  <groupId>org.springframework.boot</groupId>
  <artifactId>spring-boot-starter-hateoas</artifactId>
</dependency>
```

Gradle은 `build.gradle` 파일 안의 `dependencies`에 아래를 추가해주면 된다. (<a href="https://jeonghoon.netlify.app/Spring/SpringBoot13-hateoas/" target="_blank" title="Spring boot) Hateoas로 REST API 처리하기">출처</a>)

```gradle
implementation 'org.springframework.boot:spring-boot-starter-hateoas'
```

이 작은 라이브러리는 RESTful 서비스를 정의한 다음 클라이언트가 사용할 수 있는 형식으로 렌더링할 수 있는 구성을 제공한다.

모든 RESTful 서비스의 핵심 요소는 관련 작업에 대한 링크를 추가하는 것이다. 컨트롤러를 더욱 RESTful하게 만들려면 다음과 같은 링크를 추가하라:

[ 단일 항목 리소스 가져오기 ]

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

\* 이 자습서는 Spring MVC를 기반으로 하며, `WebMvcLinkBuilder`의 정적 헬퍼 메서드를 사용하여 이러한 링크를 빌드한다. 프로젝트에서 Spring WebFlux를 사용하는 경우, 대신 `WebFluxLinkBuilder`를 사용해야 한다.

이전 버전과 매우 유사하지만 몇 가지 사항이 변경되었다:

- 메서드의 반환 유형이 `Employee`에서 `EntityModel<Employee>`로 변경되었다. `EntityModel<T>`는 데이터뿐만 아니라 링크 컬렉션을 포함하는 Spring HATEOAS의 일반 컨테이너이다.
- `linkTo(methodOn(EmployeeController.class).one(id)).withSelfRel()`은 Spring HATEOAS가 `EmployeeController`의 `one()` 메서드에 대한 링크를 빌드하고 이를 [self](https://www.iana.org/assignments/link-relations/link-relations.xhtml) 링크로 플래그를 지정하도록 요청한다.
- `linkTo(methodOn(EmployeeController.class).all()).withRel("employees")`는 Spring HATEOAS에 집계 루트<sup>aggregate root</sup>인 `all()`에 대한 링크를 생성하고 이를 "employees"라고 호출하도록 요청한다.

"링크 구축"이 무슨 말일까? Spring HATEOAS의 핵심 타입 중 하나는 `Link`이다. 여기에는 **URI**와 **rel**(relation, 관계)이 포함된다. 링크는 웹을 강화하는 요소이다. 월드와이드웹 이전에는 다른 문서 시스템에서도 정보나 링크를 렌더링했지만, 웹을 하나로 이어주는 것은 바로 이런 관계 메타데이터로 문서와 문서를 연결하는 것이었다.

Roy Fielding은 웹을 성공으로 이끈 것과 동일한 기술로 API를 구축할 것을 권장하며, 링크는 그 중 하나이다.

애플리케이션을 다시 시작하고 *Bilbo*의 직원 기록을 쿼리하면 이전과 약간 다른 응답이 표시된다:

**<span class="green">더 보기 좋은 curl</span>**

curl 출력이 더 복잡해지면 읽기 어려워질 수 있다. 아래 명령어 또는 [다른 팁](https://stackoverflow.com/q/27238411/5432315)을 사용하여 curl이 반환하는 json을 예쁘게 정리하라:

```txt
# The indicated part pipes the output to json_pp and asks it to make your JSON pretty. (Or use whatever tool you like!)
# 표시된 부분은 출력을 json_pp로 파이프하고 JSON을 예쁘게 만들도록 요청한다. (또는 원하는 도구를 사용하라!)
#                                  v------------------v
curl -v localhost:8080/employees/1 | json_pp

# 윈도우10, command line으로 위 명령을 실행해봤는데, json_pp가 사용 불가한 명령어라 하여 실패했다. 찾아보니 json_pp는 리눅스 환경에서만 사용 가능한 명령이고 윈도우에서 같은 결과를 보려면 jq를 설치해서 json_pp 대신 jq 명령어를 써야 한다고는 하던데, 설치가 번거로워보여서 관뒀다... 설치를 하면 삭제할 줄도 알아야 하는데 설치 방법도 제대로 이해를 못해서는 삭제할 수가 없다.
# 대신 파이썬을 사용해볼 수 있다. 당연히 파이썬이 설치되어 있어야 할 것이다.
curl -v localhost:8080/employees/1 | python -m json.tool
```

[ 단일 직원에 대한 RESTful 표현 ]

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

이 압축 해제된 출력에는 앞에서 본 데이터 요소(`id`, `name`, `role`)뿐만 아니라 두 개의 URI가 포함된 `_links` 항목도 표시된다. 이 전체 문서의 형식은 [HAL](http://stateless.co/hal_specification.html)을 사용한다.

HAL은 데이터뿐만 아니라 하이퍼미디어 컨트롤도 인코딩할 수 있는 경량 [mediatype](https://tools.ietf.org/html/draft-kelly-json-hal-08)으로, 소비자에게 API의 다른 부분으로 이동할 수 있음을 알린다. 이 경우, **[집계 루트](https://www.google.com/search?q=What+is+an+aggregate+root)**<strong><sup>aggregate root</sup></strong>로 돌아가는 링크와 함께 "자체<sup>self</sup>" 링크(코드의 `this` 문과 같은 종류)가 있다.

집계 루트를 *더욱* RESTful하게 만들려면 최상위 링크를 포함*하면서* 그 안에 RESTful 컴포넌트도 포함해야 한다.

그래서 이것을

[ 집계 루트 가져오기 ]

```java
@GetMapping("/employees")
List<Employee> all() {
  return repository.findAll();
}
```

이렇게 바꾼다

[ 집계 루트 리소스 가져오기 ]

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

Wow! `repository.findAll()`에 불과했던 메서드가 이렇게 길어졌다! 걱정하지 말고 포장을 풀어보자.

`CollectionModel<>`은 또 다른 Spring HATEOAS 컨테이너로, 앞서 보았던 `EntityModel<>`처럼 단일 리소스 엔티티 대신 리소스 컬렉션을 캡슐화하는 데 목적이 있다. `CollectionModel<>` 역시 링크를 포함할 수 있다.

첫 문장을 놓치지 말라. "컬렉션을 캡슐화"한다는 것은 무슨 말일까? 직원들의 컬렉션?

그건 아니다.

REST에 대해 이야기하고 있으므로 **직원 리소스**의 컬렉션을 캡슐화해야 한다.
Since we’re talking REST, it should encapsulate collections of **employee resources**.

그렇기 때문에 모든 직원을 가져온 다음 `EntityModel<Employee>` 객체 목록으로 변환한다. (Java 8 Streams 덕분이다!)

애플리케이션을 다시 시작하고 집계 루트를 fetch하면 현재 어떤 모습인지 확인할 수 있다.

[ 직원 리소스 컬렉션의 RESTful 표현 ]

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

직원 리소스 컬렉션을 제공하는 이 집계 루트의 경우 최상위 수준인 "**self**" 링크가 있다. "**collection**"은 "**_embedded**" 섹션 아래에 나열되며, 이것이 HAL이 컬렉션을 나타내는 방식이다.

또한 컬렉션의 각 개별 멤버는 자신의 정보와 관련 링크를 가지고 있습니다.

왜 이 모든 링크를 다 추가하는 것일까? 시간이 지남에 따라 REST 서비스를 발전시킬 수 있기 때문이다. 기존 링크를 유지하면서 향후에 새로운 링크를 추가할 수 있다. 신규 클라이언트는 새로운 링크를 활용할 수 있고, 구버전<sup>legacy</sup> 클라이언트는 기존 링크를 유지할 수 있다. 이는 서비스가 이전되거나 이동하는 경우에 특히 유용하다. 링크 구조가 유지되는 한 클라이언트는 여전히 사물을 찾고 상호 작용할 수 있다.

## Simplifying Link Creation
앞의 코드에서 단일 직원 링크 생성이 반복되는 것을 보았는가? 직원에 대한 단일 링크를 제공하는 코드와 집계 루트에 대한 "employees" 링크를 생성하는 코드가 두 번 표시되었다. 이 때문에 걱정이 되었다면 다행이다! 해결책이 있다.

간단히 말해, `Employee` 객체를 `EntityModel<Employee>` 객체로 변환하는 함수를 정의해야 한다. 이 메서드를 직접 코딩할 수도 있지만, 이 작업을 대신 수행해줄 Spring HATEOAS의 `RepresentationModelAssembler` 인터페이스를 구현하면 이점이 있다.

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

이 간단한 인터페이스에는 `toModel()`이라는 하나의 메서드가 있다. 이 메서드는 모델이 아닌 객체(`Employee`)를 모델 기반 객체(`EntityModel<Employee>`)로 변환하는 것을 바탕으로 한다.

앞서 컨트롤러에서 보았던 모든 코드를 이 클래스로 옮길 수 있다. 그리고 Spring 프레임워크의 `@Component` 어노테이션을 적용하면 앱이 시작될 때 어셈블러가 자동으로 생성된다.

\* 모든 모델에 대한 Spring HATEOAS의 추상 베이스 클래스는 `RepresentationModel`입니다. 그러나 단순화를 위해 모든 POJO를 모델로 쉽게 래핑하는 메커니즘으로 `EntityModel<T>`를 사용하는 것이 좋습니다.

이 어셈블러를 활용하려면 생성자에 어셈블러를 주입하여 `EmployeeController`를 변경하기만 하면 된다.

[ EmployeeModelAssembler를 컨트롤러에 주입하기 ]

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

여기에서, 단일 항목 직원 메서드에서 해당 어셈블러를 사용할 수 있다:

[ 어셈블러를 사용하여 단일 항목 리소스 가져오기 ]

```java
@GetMapping("/employees/{id}")
EntityModel<Employee> one(@PathVariable Long id) {

  Employee employee = repository.findById(id) //
      .orElseThrow(() -> new EmployeeNotFoundException(id));

  return assembler.toModel(employee);
}
```

이 코드는 이전 것과 거의 동일하지만 여기서 `EntityModel<Employee>` 인스턴스를 생성하는 대신 어셈블러에 위임한다는 점이 다르다. 별 차이가 없어 보일 수도 있다.

집계 루트 컨트롤러 메서드에 동일한 내용을 적용하는 것이 더 인상적이다:

[ 어셈블러를 사용하여 집계 루트 리소스 가져오기 ]

```java
@GetMapping("/employees")
CollectionModel<EntityModel<Employee>> all() {

  List<EntityModel<Employee>> employees = repository.findAll().stream() //
      .map(assembler::toModel) //
      .collect(Collectors.toList());

  return CollectionModel.of(employees, linkTo(methodOn(EmployeeController.class).all()).withSelfRel());
}
```

코드는 거의 동일하지만, `EntityModel<Employee>` 생성 로직을 모두 `map(assembler::toModel)`로 대체할 수 있다. Java 8 메서드 참조 덕분에 매우 쉽게 플러그인하여 컨트롤러를 단순화할 수 있다.

\* Spring HATEOAS의 핵심 설계 목표는 올바른 일을 더 쉽게 할 수 있도록 하는 것이다. 이 시나리오에서는 하드 코딩 없이 하이퍼미디어를 서비스에 추가하는 것이다.

이 단계에서는 실제로 하이퍼미디어 기반 콘텐츠를 생성하는 Spring MVC REST 컨트롤러를 만들었다! HAL을 사용하지 않는 클라이언트는 순수한 데이터를 소비하면서 추가 비트를 무시할 수 있습니다. HAL을 사용하는 클라이언트는 권한이 부여된 API를 탐색할 수 있다.

하지만 Spring으로 진정한 RESTful 서비스를 구축하는 데 필요한 것은 이것만이 아니다. 그것은 다음에 이어서 알아보도록 하자. 이번에도 글이 길어서 나누었다.