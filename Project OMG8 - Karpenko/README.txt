OMG8 кодує uint64_t. Навряд існує табиця симолів, яку не 
покриває така кількість байтів, тому виходить, що OMG8 є 
універсальним та здатен працювати з будь-яким набором символів.

Для тестування потрібно запустити програму з першим вхідним аргументом - назвою 
файла з вхідними данними, та файла з вихідними данними. Якщо такий файл не 
вказаний, або вказаний тільки один, то зчитування й запис будуть в консолі
Наприклад для тесту з файлу можна запустити програму наступним чином:

./program.exe input.txt output.txt

Кожен тест зчитує два числа n1 n2, а потім два рядки довжини n1, n2 відповідно
Потім індекси для тестування різних функцій
Так як таблиці символів немає, то рядок довжини n мається на увазі 
n послідовних чисел від 0 до 2^64.

Для перевірки співпадання різних тестів, потрібно запустити OMG8_cross_test.cpp
та надати на вхід програмі два файли, які хочете порівняти, програма виведе 1, 
якщо зміст файлів однаковий, та 0, якщо різний
Запускати подібно до попередніх тестів:

./program.exe output1.txt output2.txt

Так як скоріш за все будуть звірятися файли з різних папок, то потрібно не забувати 
про вказання чіткого шлягу з місця заупску крос-тесту 

Крос-тест винесений в загальну папку, щоб уникнути плутанини з функціями main
та була можливість зручно компілювати всі три екзешники


add приймає індекс куди вставляти та набір символів, що треба вставити,
що вирішує всі проблеми (додавання в кінець, в середину та на початок)
Для роботи з підрядками просто використоуємо вункцію cut, що вертає 
підрядок

find повертає індекс, на якому починається рядок, який ми шукаємо.
та -1, якщо такого немає

encode та decode переводять нашу строку в вектор байтів і назад за
правилами, що прописані в умові задачі

read(int n)  считує n символів

для зміни рядка є оператор [], що повертає символ по заданому індексу

int toInt(int dim) перевіряє, чи є задий рядок числом в  данній системі
і повертає значення цього числа, або -1, якщо не є числом 
(також може повернути -1, якщо число буде дуже великим)

fromInt переводить число в рядок з заданою системою

Так як таблиці символів в мене немає, то при перевірці на те, чи є
рядок числом в будь-якій системі, будемо вважати, що код і-тої цифри - і.
