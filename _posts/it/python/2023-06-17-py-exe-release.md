---
title: "[python] GUI 프로그램 exe 만들고 배포하기, 소멸자와 로깅"
author: dapin1490
date: 2023-06-17T19:49:00+09:00
categories: [IT, python]
tags: [지식, IT, python, exe, 배포, 소멸자, GUI]
render_with_liquid: false
---

<style>
  figure { text-align: center; }
</style>

## ToC
- [파이썬 GUI PyQt5](#파이썬-gui-pyqt5)
- [exe 만들기 PyInstaller](#exe-만들기-pyinstaller)
- [소멸자와 로그 남기기](#소멸자와-로그-남기기)
- [참고 자료](#참고-자료)

# 파이썬 GUI PyQt5
밥 메뉴를 고르는 게 귀찮아서 룰렛을 돌릴 때가 가끔 있는데, 그때마다 인터넷으로 룰렛을 검색해서 돌리는 게 더 귀찮아서 룰렛 프로그램을 직접 만들었다. 처음엔 C++로 콘솔 텍스트 출력만 이용해서 만들었는데, GUI로도 만들면 좋을 것 같아서 뭘 할 수 있을까 찾아봤었다. 처음부터 C++로 만들었으니까 GUI도 C++로 만들고 싶었는데, 찾아서 나오는 것들이 하나같이 영 어려워 보여서 파이썬으로 바꿨다. 파이썬은 PyQt5로 GUI를 만들 수 있다고 해서 보니까 코드가 꽤 쉬워서 기본 기능만 조금 익혀서 일단 완성했다.

PyQt5 배우는 건 [PyQt5 Tutorial - 파이썬으로 만드는 나만의 GUI 프로그램](https://wikidocs.net/book/2165) 보면서 했고, 완성한 프로그램은 [dapin1490/roulette_exe](https://github.com/dapin1490/roulette_exe)에 [v230615-h17-40](https://github.com/dapin1490/roulette_exe/releases/tag/v230615-h17-40) 버전으로 배포했다. 릴리즈가 몇 개 더 있긴 한데, 이것보다 앞선 릴리즈는 C++로 만들었던 프로그램이다.

프로그램 자체는 아주 간단해서 하루만에도 다 만들 수 있었지만 나름 배운 건 있었다. GUI 프로그램을 만들 때는 버튼, 입력칸, 텍스트 등등 부품을 조립한다고 생각하면 좀 이해하기 좋더라. 필요한 컴포넌트를 생성하고, 스타일 꾸미고, 적절한 기능 연결하고, 마지막으로 레이아웃에 배치. 프로그램마다 다를 수는 있겠지만 큰 흐름은 이렇게 되는 것 같다.

# exe 만들기 PyInstaller
비주얼 스튜디오는 빌드 메뉴로 바로 exe 파일을 만들 수 있고, 일부 설정만 조금 만지면 배포도 가능하다. 근데 파이썬이나 파이참은 그런 메뉴를 못봐서 찾아보니까 `PyInstaller`를 사용하면 된다고 한다.

`PyInstaller`는 터미널에서 `pip`으로 설치하면 되고, 사용할 때는 터미널로 exe 파일을 저장할 곳에 가서 `pyinstaller -w -F {작성한 코드 파일 경로}`로 실행하면 exe 파일을 만들 수 있다. `-w` 옵션은 완성된 exe 파일을 실행했을 때 콘솔창이 따로 뜨지 않게 하고, `-F`는 별도의 파일 없이 exe 파일 하나로 완성되게 한다.

# 소멸자와 로그 남기기
룰렛은 간단한 GUI도 만들어봤고 exe도 해봤으니까 이번에는 시험 공부도 할 겸 디자인 패턴 필기 자료를 읽어서 랜덤으로 문제를 내는 프로그램을 만들었는데, 점수 기록을 위해 프로그램 종료 시 세이브 파일에 기록을 남기게 하려고 했다. 가장 처음 한 생각은 *어차피 프로그램이 종료될 때 소멸자가 실행될 거니까, 소멸자에서 세이브 파일을 수정하고 끝내면 되겠다* 였는데 여기서 문제가 생겼었다. `open` 함수로 파일을 열어 프로그램 실행 기록을 남기고 다시 닫아야 하는데 해당 함수가 정의되어 있지 않다는 오류가 자꾸 났다. 오류 메시지는 `NameError: name 'open' is not defined When trying to log to files`였다.

오류 메시지로 검색을 해보니 인터프리터가 종료될 때 가비지 콜렉터가 `open` 함수를 삭제하는 게 소멸자보다 빨리 실행돼서 소멸자 입장에서는 `open`이 정의되어 있지 않은 게 문제라고 했다. 해결 방법은 로그 작성이 소멸자보다 먼저 실행되게, 명시적으로 실행하는 것. 고치니까 바로 해결됐다. 여기서 새로운 걸 배웠다. 파이썬 인터프리터가 종료될 때, 소멸자보다 먼저 삭제되는 함수가 있고, 그 경우 소멸자에서는 사용할 수 없다.

# 참고 자료
* [PyQt5 Tutorial - 파이썬으로 만드는 나만의 GUI 프로그램](https://wikidocs.net/book/2165)
* [PyQt5 Tutorial - 파이썬으로 만드는 나만의 GUI 프로그램 / 09. 실행파일 만들기 (PyInstaller)](https://wikidocs.net/21952)
* [NameError: name 'open' is not defined When trying to log to files](https://stackoverflow.com/questions/64679139/nameerror-name-open-is-not-defined-when-trying-to-log-to-files)
