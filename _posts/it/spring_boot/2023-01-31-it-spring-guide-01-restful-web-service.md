---
title: "[Spring TUTORIAL] Building a RESTful Web Service"
author: dapin1490
date: 2023-01-31T00:00:00+09:00
categories: [IT, Spring Boot]
tags: [지식, IT, Spring, Spring Boot, Gradle, Tutorial]
render_with_liquid: false
---

## Table of Contents
- [관련 글 보기](#관련-글-보기)
- [사전 지식](#사전-지식)
  - [REST](#rest)
  - [Gradle](#gradle)
- [Building a RESTful Web Service](#building-a-restful-web-service)
  - [What You Will Build](#what-you-will-build)
  - [What You Need](#what-you-need)
  - [How to complete this guide](#how-to-complete-this-guide)
  - [Starting with Spring Initializr](#starting-with-spring-initializr)
    - [프로젝트 초기 실행 시 발생했던 오류](#프로젝트-초기-실행-시-발생했던-오류)
  - [Create a Resource Representation Class](#create-a-resource-representation-class)
  - [Create a Resource Controller](#create-a-resource-controller)
  - [Build an executable JAR](#build-an-executable-jar)
    - [윈도우에서 Gradle 빌드하고 실행하기](#윈도우에서-gradle-빌드하고-실행하기)
  - [Test the Service](#test-the-service)
    - [실행한 서버 끝내기](#실행한-서버-끝내기)
  - [Summary](#summary)
  - [See Also](#see-also)
- [참고 자료](#참고-자료)

*\* 일부 문단에서 번역기 사용함*  
*\* 일부 문단에 직접 해결했던 오류나 추가로 찾아봤던 내용을 같이 기록함(한글 소제목으로 된 문단)*

# 관련 글 보기
- [[Spring TUTORIAL] Building REST services with Spring (1)](https://dapin1490.github.io/posts/it-spring-guide-02-build-rest-service-01/)

# 사전 지식

## REST
Representational State Transfer의 약자로 자원을 이름으로 구분하여 해당 자원의 상태를 주고받는 모든 것을 의미한다고 한다.<sup><a id="body-ref-01" href="#ref-01" target="_blank" title="[네트워크] REST API란? REST, RESTful이란?">[1]</a></sup> 이때 자원의 이름을 `URI(Uniform Resource Identifier)`라고 한다.  
  
REST의 요점은 크게 두 가지로 정리할 수 있다.<sup><a id="body-ref-02" href="#ref-02" target="_blank" title="REST API 제대로 알고 사용하기">[2]</a></sup>  
1. URI는 정보의 자원을 표현해야 한다.  
2. 자원에 대한 행위는 HTTP Method(GET, POST, PUT, DELETE)로 표현한다.  

자세한 사항은 참고 자료 [1, 2]를 읽어보자.  

## Gradle
안드로이드 스튜디오를 사용해봤다면 Gradle이라는 이름의 폴더나 파일은 본 적이 있을 것이다. 그 Gradle이다. 지금은 spring으로 프로젝트를 만들고 사용하고 관리하는 데에 필요하다. 내가 프로젝트 생성 후 실행해보면서 이것저것 찾아보니, 꼭 Gradle을 설치할 필요는 없다고 한다.  
  
Gradle은 오픈 소스 빌드 자동화 도구이고 거의 모든 종류의 소프트웨어를 빌드할 수 있을 만큼 유연하다. Gradle은 사용자가 무엇을 또는 어떻게 빌드하려고 하는지에 대해 몇 가지 가정(assumption)을 하고, 이것이 특히 Gradle을 유연하게 만든다.<sup><a id="body-ref-03" href="#ref-03" target="_blank" title="What is Gradle?">[3]</a></sup>  
  
나도 이제 처음 배워서 잘 모른다. 요점은 **빌드 관리를 위한 도구**라는 것만 기억하면 된다. 나머지는 가이드를 보고 따라하기만 해도 반은 간다. <a href="#ref-03" target="_blank" title="What is Gradle?">참고 자료 [3]</a>을 보면 된다.  

# Building a RESTful Web Service
원문 보기: [Building a RESTful Web Service](https://spring.io/guides/gs/rest-service/)  

이 가이드는 Spring으로 "Hello, World"를 생성하는 RESTful한 웹 서비스를 만든다.  

## What You Will Build
이 가이드를 통해 <http://localhost:8080/greeting>에서 HTTP GET 요청을 받는 서비스를 만들 수 있다.  
  
그 요청은 아래 보이는 것처럼 greeting의 JSON 형식 응답을 보낼 것이다:

```json
{"id":1,"content":"Hello, World!"}
```

아래와 같이 쿼리 문자열에 `name` 파라미터를 추가해 greeting을 커스터마이즈할 수 있다.  
<http://localhost:8080/greeting?name=User>  

`name` 파라미터의 값이 `World`라는 디폴트 값을 대체해 응답에 반영되고, 결과는 다음과 같다:

```json
{"id":1,"content":"Hello, User!"}
```

## What You Need
- 15분 정도 *(오류가 하나도 발생하지 않는다는 전제로 15분이고, 오류 하나 잘못 걸리면 며칠은 필요하다)*
- 가장 선호하는 텍스트 편집기나 IDE
- <a href="https://www.oracle.com/java/technologies/downloads/" target="_blank">Java 17</a> 혹은 그 이상
- <a href="https://gradle.org/install/" target="_blank">Gradle 7.5+</a> 또는 <a href="https://maven.apache.org/download.cgi" target="_blank">Maven 3.5+</a>
- 코드를 IDE로 바로 가져올 수도 있다:  
  - <a href="https://spring.io/guides/gs/sts" target="_blank">Spring Tool Suite (STS)</a>
  - <a href="https://spring.io/guides/gs/intellij-idea/" target="_blank">IntelliJ IDEA</a>
  - <a href="https://spring.io/guides/gs/guides-with-vscode/" target="_blank">VSCode</a>

## How to complete this guide
대부분의 <a href="https://spring.io/guides" target="_blank">Getting Started guides</a>처럼, 처음부터 시작해서 단계별로 끝낼 수도 있고, 이미 할 줄 아는 기본 세팅은 넘기고 할 수 있다. 어느 쪽으로 하든, 마지막엔 제대로 작동하는 코드를 갖게 될 것이다.  

**처음부터 시작하려면** [Starting with Spring Initializr](#starting-with-spring-initializr) 문단으로 가면 된다.  

**기본은 넘긴다면** 아래와 같이 하면 된다.  

- 이 가이드의 레포지토리를 [다운](https://github.com/spring-guides/gs-rest-service/archive/main.zip)받고 압축을 풀거나, [Git](https://spring.io/understanding/Git)을 이용해 클론하라(`git clone https://github.com/spring-guides/gs-rest-service.git`).
- `gs-rest-service/initial` 폴더로 간다.
- [Create a Resource Representation Class](#create-a-resource-representation-class) 문단으로 간다.  
  
**다 하고 나면** `gs-rest-service/complete` 폴더의 코드와 결과를 비교해볼 수 있다.  

## Starting with Spring Initializr
[미리 초기화된 프로젝트](https://start.spring.io/#!type=maven-project&groupId=com.example&artifactId=rest-service&name=rest-service&description=Demo%20project%20for%20Spring%20Boot&packageName=com.example.rest-service&dependencies=web)를 이용해 Generate를 클릭하고 ZIP 파일을 다운받을 수 있다. 이 프로젝트는 이 튜토리얼에 맞게 설정되어 있다.  

프로젝트를 직접 초기화하고 싶다면 다음과 같이 하면 된다:  

1. <https://start.spring.io>로 간다. 이 서비스는 응용 프로그램에 필요한 모든 종속성을 가져오고 대부분의 설정을 수행한다.
2. Gradle 또는 Maven 중 하나를 선택하고 사용할 언어를 선택한다. 이 가이드는 Java를 선택했다고 가정한다.
3. **Dependencies**를 클릭하고 **Spring Web**을 선택한다.
4. **Generate**를 클릭한다.
5. 결과 ZIP 파일을 다운로드한다. 이 파일은 선택한 항목으로 구성된 웹 응용프로그램의 아카이브이다.

\* IDE에 Spring Initializer가 통합되어 있는 경우 IDE에서 이 과정을 완료할 수 있다.  
\* 또한 Github에서 프로젝트를 포크하여 IDE 또는 다른 편집기에서 열 수 있다.  

### 프로젝트 초기 실행 시 발생했던 오류
나는 <https://start.spring.io>에서 초기화한 프로젝트를 IntelliJ IDEA로 열어서 이후의 과정을 따라가려고 했었다. 이때 IDE가 자동으로 빌드를 실행했었는데, 아래와 같은 오류 메시지가 길게 뜨면서 매번 빌드에 실패하는 문제가 있었다(지금은 해결한 오류라 오류 메시지는 구글에 검색해서 가져왔다).  

```txt
A problem occurred configuring root project '(프로젝트명)'.
> Could not resolve all files for configuration ':classpath'.
   > Could not resolve org.springframework.boot:spring-boot-gradle-plugin:3.0.1.
     Required by:
         project : > org.springframework.boot:org.springframework.boot.gradle.plugin:3.0.1
```

저 오류 메시지의 일부를 복사해 검색해보면 인텔리제이를 업데이트해야 한다든가([링크](https://nahwasa.com/entry/%EC%8A%A4%ED%94%84%EB%A7%81%EB%B6%80%ED%8A%B8-300-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EC%83%9D%EC%84%B1%EC%8B%9C-%EC%97%90%EB%9F%AC-%ED%95%B4%EA%B2%B0%EB%B2%95-%EC%9D%B8%ED%85%94%EB%A6%AC%EC%A0%9C%EC%9D%B4)), 프로젝트 설정의 자바 버전 문제라든가([링크](https://nahwasa.com/entry/%EC%8A%A4%ED%94%84%EB%A7%81%EB%B6%80%ED%8A%B8-300-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EC%83%9D%EC%84%B1%EC%8B%9C-%EC%97%90%EB%9F%AC-%ED%95%B4%EA%B2%B0%EB%B2%95-%EC%9D%B8%ED%85%94%EB%A6%AC%EC%A0%9C%EC%9D%B4)), 스프링부트와 자바 버전이 맞지 않는 것이 문제라든가([링크](https://velog.io/@jollypyun/%EC%98%A4%EB%A5%98-%EA%B8%B0%EB%A1%9DCould-not-resolve-org.springframework.bootspring-boot-gradle-plugin3.0.1)) 등등 원인과 그에 따른 해결 방법은 다양하게 찾을 수 있었지만 나는 저것 중 어떤 방법도 통하지 않았었다.  

결국 스프링부트 버전을 2.X로 내려서 빌드에 성공했었는데, 나중에 밝혀진 바로는 내 노트북에 설정된 시스템 변수 `JAVA_HOME`이 11 버전으로 설정되어 있던 게 문제였다([링크](https://devlifetestcase.tistory.com/7)). 구글에 나오는 방법은 다 해봤는데도 자꾸 오류가 난다면 `JAVA_HOME`을 확인해보자.  

## Create a Resource Representation Class
이제 프로젝트 및 빌드 시스템을 설정했으므로 웹 서비스를 만들 수 있다.  

서비스 상호 작용에 대해 생각하는 것으로 프로세스를 시작한다.  

이 서비스는 `/greeting`에 대한 `GET` 요청을 처리할 것이며, `name` 파라미터를 쿼리 문자열에 넣는 것은 선택사항이다(필수가 아니다). `GET` 요청은 greeting을 나타내는 JSON이 포함된 `200 OK` 응답을 반환해야 한다. 출력은 다음과 유사해야 한다:

```json
{
    "id": 1,
    "content": "Hello, World!"
}
```

`id`는 greeting의 고유 식별자이고 `content`는 greeting의 텍스트 표현이다.  

greeting 표현을 모델링하기 위해 리소스 표현 클래스를 만든다(*인텔리제이로 한다면 '레코드 클래스'를 만들면 된다*). 그러기 위해 `id` 및 `content` 데이터에 대한 Java 레코드 클래스를 다음과 같이 제공한다(파일은 `src/main/java/com/example/restservice/Greeting.java`).  

```java
package com.example.restservice;

public record Greeting(long id, String content) { }
```

이 응용 프로그램은 [Jackson JSON](https://github.com/FasterXML/jackson) 라이브러리를 사용하여 `Greeting` 유형의 인스턴스를 JSON에 자동으로 병합한다. Jackson은 web starter에 기본적으로 포함되어 있다.  

## Create a Resource Controller
RESTful 웹 서비스를 구축하는 Spring의 접근 방식에서 HTTP 요청은 컨트롤러에 의해 처리된다. 이러한 구성 요소는 `@RestController` 주석으로 식별되며, 아래에 있는 `GreetingController`는 `Greeting` 클래스의 새 인스턴스를 반환하여 `/greeting`에 대한 `GET` 요청을 처리한다.  

*\* 다시 말해 HTTP 요청을 처리하는 컨트롤러는 `@RestController`가 붙어야 하고, `GET` 요청을 처리하는 메소드는 `GreetingController`이다. `GreetingController`는 `@GetMapping("/greeting")`을 통해 `/greeting`에 대한 `GET` 요청을 처리하도록 매핑된다.*

```java
package com.example.restservice;

import java.util.concurrent.atomic.AtomicLong;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class GreetingController {

    private static final String template = "Hello, %s!";
    private final AtomicLong counter = new AtomicLong();

    @GetMapping("/greeting")
    public Greeting greeting(@RequestParam(value = "name", defaultValue = "World") String name) {
        return new Greeting(counter.incrementAndGet(), String.format(template, name));
  }
}
```

이 컨트롤러는 간결하고 단순하지만, 많은 일이 일어나고 있다. 우리는 그것을 단계적으로 분해한다.  

`@GetMapping` 주석을 사용하면 `/greeting`에 대한 HTTP GET 요청이 `greeting()` 메서드에 매핑된다.  

\* 다른 HTTP 동사에 대한 동반 주석(companion annotation)(예: POST의 경우 `@PostMapping`)이 있다. 또한 이들 모두가 파생된 `@RequestMapping` 주석이 있으며 동의어 역할을 할 수 있다(예: `@RequestMapping(method=GET)`).  

`@RequestParam`은 쿼리 문자열 매개 변수 `name`의 값을 `greeting()` 메서드의 `name` 매개 변수에 바인딩한다. 요청에 `name` 매개 변수가 없으면 `defaultValue`의 `World`가 사용된다.  

메서드 본문의 구현은 `counter`의 다음 값을 기반으로 `id` 및 `content` 속성을 가진 새로운 `Greeting` 객체를 생성하고 반환하며 `template`을 사용하여 주어진 `name`을 포맷한다(format).  

기존 MVC 컨트롤러와 앞에서 설명한 RESTful 웹 서비스 컨트롤러의 주요 차이점은 HTTP 응답 본문이 생성되는 방식이다. 이 RESTful 웹 서비스 컨트롤러는 뷰 기술을 사용하여 데이터를 HTML로 렌더링하는 대신 `Greeting` 객체를 채워서 반환한다. 객체 데이터는 HTTP 응답에 JSON으로 직접 기록된다.  

이 코드는 Spring `@RestController` 주석을 사용하는데, 이 주석은 클래스를 '모든 메서드가 뷰 대신 도메인 객체를 반환하는 컨트롤러'로 표시한다. 이는 `@Controller`와 `@ResponseBody`를 모두 포함하는 줄임말이다.  

`Greeting` 객체를 JSON으로 변환해야 한다. Spring의 HTTP 메시지 변환기 지원 덕분에 이 변환을 수동으로 수행할 필요가 없다. [Jackson 2](https://github.com/FasterXML/jackson)가 클래스 경로에 있으므로 Spring의 `MappingJackson2HttpMessageConverter`가 자동으로 선택되어 `Greeting` 인스턴스를 JSON으로 변환한다.  

`@SpringBootApplication`은 다음을 모두 추가하는 편리한 주석이다:

- `@Configuration`: 클래스를 응용 프로그램 컨텍스트의 빈 정의(bean definition) 원본(source)으로 태그한다.
- `@EnableAutoConfiguration`: 클래스 경로 설정, 기타 bean 및 다양한 속성 설정에 따라 bean 추가를 시작하도록 스프링 부트에 지시한다. 예를 들어 `spring-webmvc`가 클래스 경로에 있는 경우 이 주석은 응용 프로그램을 웹 응용 프로그램으로 플래그 지정하고 `DispatcherServlet` 설정과 같은 주요 동작을 활성화한다.
- `@ComponentScan`: 스프링에게 `com/example` 패키지에서 다른 구성 요소, 구성 및 서비스를 구해(look for) 컨트롤러를 찾도록(find) 한다.

`main()` 메서드는 SpringBoot의 `SpringApplication.run()` 메서드를 사용하여 응용 프로그램을 시작한다. XML 행이 하나도 없다는 것을 아는가? `web.xml` 파일도 없다. 이 웹 애플리케이션은 100% 순수 Java이므로 plumbing 또는 인프라 구성(infrastructure)을 처리할 필요가 없었다.  

## Build an executable JAR
Gradle 또는 Maven을 사용하여 command line에서 애플리케이션을 실행할 수 있다. 또한 필요한 모든 종속성, 클래스 및 리소스를 포함하는 단일 실행 파일인 JAR 파일을 생성하여 실행할 수도 있다. 실행 가능한 jar를 구축하면 개발 라이프사이클 전반에 걸쳐 다양한 환경에서 애플리케이션으로 서비스를 쉽게 제공, 버전 관리 및 구현할 수 있다.  

Gradle을 사용하는 경우 `./gradlew bootRun`을 사용하여 응용 프로그램을 실행할 수 있다. 또는 `./gradgrew build`를 사용하여 JAR 파일을 빌드한 다음 다음과 같이 JAR 파일을 실행할 수 있다:

```shell
java -jar build/libs/gs-rest-service-0.1.0.jar
```

Maven을 사용하는 경우 `./mvnw spring-boot:run`을 사용하여 애플리케이션을 실행할 수 있다. 또는 다음과 같이 `./mvnw clean package`로 JAR 파일을 빌드한 다음 JAR 파일을 실행할 수 있다:

```shell
java -jar target/gs-rest-service-0.1.0.jar
```

\* 여기에 설명된 단계는 실행 가능한 JAR을 생성한다. [클래식 WAR 파일 구축](https://spring.io/guides/gs/convert-jar-to-war/)도 가능하다.  

로깅 출력이 표시된다. 서비스가 몇 초 안에 시작되고 실행될 것이다.

### 윈도우에서 Gradle 빌드하고 실행하기
위에 나온 것과 달리 윈도우는 `gradlew`로 빌드하거나 실행할 때 `./`를 붙이지 않는다([링크](https://kotlinworld.com/314)). 나는 이걸 몰라서 빌드만 하는데도 시간이 좀 걸렸었다.  

나는 cmd를 잘 몰라서 저 명령어 말고도 실행하는 방법 자체를 여기저기 찾아봤었는데, 가이드에서 자세히 알려주지 않은 몇 가지 과정이 있었다. (바로 실행하는 건 안 해봤고 빌드 후 실행하는 것만 해봤다)  

1. 빌드를 하기 전에 프로젝트 내에 `build/` 폴더를 미리 만들어 둔다. (처음부터 만들고 한 거라 안 하면 어떻게 되는지는 모른다)
2. cmd에 `cd 프로젝트경로`를 입력해 프로젝트 폴더로(정확히는 `gradlew` 파일이 있는 위치로) 이동한다.
3. `gradlew build`를 입력하면 바로 빌드가 생긴다.
4. 빌드 후 생성된 jar 파일의 이름을 알아야 한다. 아까 만들어둔 `build/` 폴더의 `build/libs/` 폴더에 들어가서 직접 jar 파일의 이름을 확인해도 되고, `build.gradle` 파일과 `settings.gradle` 파일에서 버전명(`version`)과 프로젝트명(`rootProject.name`)을 확인하고 조합해도 된다. 조합 방식은 `build/libs/프로젝트명-버전.jar`이다. 언더바(`_`)와 하이픈(`-`)을 구분한다.
5. 4번에서 확인한 jar 파일 이름으로 실행 명령어를 쓴다. `java -jar build/libs/프로젝트명-버전.jar`이다.
6. Spring 아스키 아트가 뜨면 성공한 것이다. 이대로 cmd를 켜둔 채 다음 과정을 진행하면 된다.

덧붙여, `gradlew`를 사용한다면 Gradle을 굳이 설치할 필요는 없다([참고 1](https://gihyun.com/120), [참고 2](https://kotlinworld.com/314)).  

## Test the Service
서비스가 시작되었으니 <http://localhost:8080/greeting>을 방문하면 다음을 확인할 수 있다:

```json
{"id":1,"content":"Hello, World!"}
```

<http://localhost:8080/greeting?name=User>을 방문하여 `name` 쿼리 문자열 매개 변수를 추가해보라. 다음 결과에서 알 수 있듯이 `content` 속성의 값이 `Hello, World!`에서 `Hello, User!`로 바뀌는 것을 볼 수 있다.

```json
{"id":2,"content":"Hello, User!"}
```

이러한 변경은 `GreetingController`의 `@RequestParam`이 예상대로 작동하고 있음을 보여준다. `name` 매개 변수에는 기본값인 `World`가 지정되었지만 쿼리 문자열을 통해 명시적으로 재정의할 수 있다.  

또한 `id` 속성이 `1`에서 `2`로 변경된 것을 확인하라. 이는 여러 요청에 걸쳐 동일한 `GreetingController` 인스턴스에 대해 작업하고 있으며 예상대로 각 호출에서 해당 `counter` 필드가 증가하고 있음을 보여준다.  

### 실행한 서버 끝내기
많은 가이드가 그렇듯, 시작하는 방법은 가르쳐줬지만 끝내는 방법은 가르쳐주지 않아서 찾아봤다. 여러 가지 방법이 있긴 했는데 내가 잘 써먹지 못한 것 같지만 이걸 참고해서 잘 쓸 수 있는 사람이 있을지도 모르니까 써두겠다.  

1. 서버 실행하던 cmd 창 끄기: 가장 투박하고 별로 좋지 않아보이는 방법이지만 지금같은 연습 단계에서는 이래도 된다.
2. Graceful Shutdown 사용하기([블로그](https://blog.marcosbarbero.com/graceful-shutdown-spring-boot-apps/), [코드(깃허브)](https://github.com/weekly-drafts/graceful-shutdown-spring-boot/blob/master/src/main/java/com/marcosbarbero/wd/gracefulshutdown/GracefulShutdown.java)): 블로그도 보고 깃허브도 보면서 똑같이 코드를 추가해두긴 했는데, 어떻게 '종료를 실행시키는지' 몰라서 못써먹었다.
3. `taskkill` 명령어 쓰기([블로그](https://blog.naver.com/afidev/20189044670)): 방황 끝에 내가 성공한 방법이다. 서버를 실행하고 있는 프로세스의 PID를 이용해 강제로 종료한다. PID는 [이 코드](https://heowc.dev/2018/12/27/spring-boot-graceful-shutdown/#pid-%EA%B5%AC%ED%95%98%EA%B8%B0)를 참고해서 알아낼 수도 있다고 하고(난 실패했음), 서버를 실행중인 cmd 창의 로그에서 찾을 수도 있다.  
    예를 들어 cmd에 출력된 로그가 `2018-06-28 20:37:28.296  INFO 6578 --- [           main] c.m.wd.gracefulshutdown.Application      : Started Application in 2.158 seconds (JVM running for 2.591)`라고 할 때([출처](https://blog.marcosbarbero.com/graceful-shutdown-spring-boot-apps/#:~:text=a%20SIGTERM.-,Locate%20the%20process%20id,-When%20you%20start)), PID는 `INFO` 옆에 있는 `6578`이다. 매번 실행할 때마다 달라진다.  
    추가로, 서버를 실행중인 cmd 창은 명령어를 더 입력할 수 없으니 새 cmd 창을 열어 `taskkill`을 실행해야 한다. 서버 종료는 `/F` 옵션을 추가해 강제로 종료해야 한다(오류 메시지가 알려줬다).  


## Summary
Congratulations! You have just developed a RESTful web service with Spring.  
축하! 당신은 방금 Spring과 함께 RESTful 웹 서비스를 개발했다.  


## See Also
The following guides may also be helpful:  
다음 가이드도 도움이 될 수 있다:  

- [Accessing GemFire Data with REST](https://spring.io/guides/gs/accessing-gemfire-data-rest/)
- [Accessing MongoDB Data with REST](https://spring.io/guides/gs/accessing-mongodb-data-rest/)
- [Accessing data with MySQL](https://spring.io/guides/gs/accessing-data-mysql/)
- [Accessing JPA Data with REST](https://spring.io/guides/gs/accessing-data-rest/)
- [Accessing Neo4j Data with REST](https://spring.io/guides/gs/accessing-neo4j-data-rest/)
- [Consuming a RESTful Web Service](https://spring.io/guides/gs/consuming-rest/)
- [Consuming a RESTful Web Service with AngularJS](https://spring.io/guides/gs/consuming-rest-angularjs/)
- [Consuming a RESTful Web Service with jQuery](https://spring.io/guides/gs/consuming-rest-jquery/)
- [Consuming a RESTful Web Service with rest.js](https://spring.io/guides/gs/consuming-rest-restjs/)
- [Securing a Web Application](https://spring.io/guides/gs/securing-web/)
- [Building REST services with Spring](https://spring.io/guides/tutorials/rest/)
- [React.js and Spring Data REST](https://spring.io/guides/tutorials/react-and-spring-data-rest/)
- [Building an Application with Spring Boot](https://spring.io/guides/gs/spring-boot/)
- [Creating API Documentation with Restdocs](https://spring.io/guides/gs/testing-restdocs/)
- [Enabling Cross Origin Requests for a RESTful Web Service](https://spring.io/guides/gs/rest-service-cors/)
- [Building a Hypermedia-Driven RESTful Web Service](https://spring.io/guides/gs/rest-hateoas/)
- [Circuit Breaker](https://spring.io/guides/gs/circuit-breaker/)

새로운 가이드를 작성하거나 기존 가이드에 기여하고 싶은가? [contribution guidelines](https://github.com/spring-guides/getting-started-guides/wiki)를 확인하라.  

모든 가이드는 코드에 대한 ASLv2 라이선스와 저작물에 대한 [Attribution, NoDerivatives creative commons license](https://creativecommons.org/licenses/by-nd/3.0/)를 가지고 출시된다.

# 참고 자료
[<a id="ref-01" href="#body-ref-01">1</a>] \[네트워크] REST API란? REST, RESTful이란?, <a href="https://khj93.tistory.com/entry/%EB%84%A4%ED%8A%B8%EC%9B%8C%ED%81%AC-REST-API%EB%9E%80-REST-RESTful%EC%9D%B4%EB%9E%80" target="_blank">https://khj93.tistory.com/entry/네트워크-REST-API란-REST-RESTful이란</a>  
[<a id="ref-02" href="#body-ref-02">2</a>] REST API 제대로 알고 사용하기, <a href="https://meetup.nhncloud.com/posts/92" target="_blank">https://meetup.nhncloud.com/posts/92</a>  
[<a id="ref-03" href="#body-ref-03">3</a>] What is Gradle?, <a href="https://docs.gradle.org/current/userguide/what_is_gradle.html" target="_blank">https://docs.gradle.org/current/userguide/what_is_gradle.html</a>  

- 스프링부트 3.0.0 프로젝트 생성시 에러 해결법 (인텔리제이), <a href="https://nahwasa.com/entry/%EC%8A%A4%ED%94%84%EB%A7%81%EB%B6%80%ED%8A%B8-300-%ED%94%84%EB%A1%9C%EC%A0%9D%ED%8A%B8-%EC%83%9D%EC%84%B1%EC%8B%9C-%EC%97%90%EB%9F%AC-%ED%95%B4%EA%B2%B0%EB%B2%95-%EC%9D%B8%ED%85%94%EB%A6%AC%EC%A0%9C%EC%9D%B4" target="_blank">https://nahwasa.com/entry/스프링부트-300-프로젝트-생성시-에러-해결법-인텔리제이</a>
- \[오류 기록]Could not resolve org.springframework.boot:spring-boot-gradle-plugin:3.0.1., <a href="https://velog.io/@jollypyun/%EC%98%A4%EB%A5%98-%EA%B8%B0%EB%A1%9DCould-not-resolve-org.springframework.bootspring-boot-gradle-plugin3.0.1" target="_blank">https://velog.io/@jollypyun/오류-기록Could-not-resolve-org.springframework.bootspring-boot-gradle-plugin3.0.1</a>
- \[Spring Boot / Error] 빌드 시 "Execution failed for task ':compileJava'.> invalid source release: 11" 에러 발생, <a href="https://devlifetestcase.tistory.com/7" target="_blank">https://devlifetestcase.tistory.com/7</a>
- gradlew와 gradle.bat 을 사용해 gradle 설치하지 않고 사용하기, <a href="https://kotlinworld.com/314" target="_blank">https://kotlinworld.com/314</a>
- 3 . gradlew (gradle wrapper) - spring 사용하기, <a href="https://gihyun.com/120" target="_blank">https://gihyun.com/120</a>
- Graceful Shutdown Spring Boot Applications, <a href="https://blog.marcosbarbero.com/graceful-shutdown-spring-boot-apps/" target="_blank">https://blog.marcosbarbero.com/graceful-shutdown-spring-boot-apps/</a>
- weekly-drafts/graceful-shutdown-spring-boot - GracefulShutdown.java, <a href="https://github.com/weekly-drafts/graceful-shutdown-spring-boot/blob/master/src/main/java/com/marcosbarbero/wd/gracefulshutdown/GracefulShutdown.java" target="_blank">https://github.com/weekly-drafts/graceful-shutdown-spring-boot/blob/master/src/main/java/com/marcosbarbero/wd/gracefulshutdown/GracefulShutdown.java</a>
- \[윈도우 서버] cmd 프로세스 kill 명령어, <a href="https://blog.naver.com/afidev/20189044670" target="_blank">https://blog.naver.com/afidev/20189044670</a>
- Spring Boot - 안전하게 종료시키기, <a href="https://heowc.dev/2018/12/27/spring-boot-graceful-shutdown/" target="_blank">https://heowc.dev/2018/12/27/spring-boot-graceful-shutdown/</a>
