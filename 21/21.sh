#! /usr/bin/env bash

#Алгоритм Цезаря by Alrott SlimRG

if [[ $* = "" ]]; then echo 'Вы ничего не ввели, Вы же не хотите зашифровать весь диск :)'; exit 404; fi  #Если ничего не введено 

#if [[ $0 != '/usr/bin/rch' ]]; then echo "Не знаю как вы смогли получить данную ошибку, но не надо так :("; exit 812; fi  #Если путь к программе неверный

R=0;
S=3;
E=0;
SECF=0;

TEXD="";
DIR="";


while  ((1 <= $#)); #Проходим по всем параметрам
do
 if [[ ${1:0:1} = "-" ]]; then 
  TEMP=$1;
 
  while [[ ${TEMP:0:1} = "-" ]]; do
   TEMP=${TEMP:1:${#TEMP}};
  done;
  
  while [[ $TEMP != "" ]]; do
   if [[ ${TEMP:0:4} = "help" ]]; then
    echo;
    echo " rch, версия 1.2.05(1)-release-(x86_64-pc-linux-gnu)"
    echo;
    echo " Использование:  rch [ключи] [адресс папки] [адресс папки] ... [.расширение] [.расширение] ..."
    echo;
    echo "  Длинные параметры: "   
    echo "   -t - только txt файлы (по умолчанию выкл.)"
    echo "   -r - рекурсия (по умолчанию выкл.)"
    echo "   -s[number] - смещение (по умолчанию 3), где number"
    echo "   -e - сохранить оригиналы с расширением .or"
    echo "   -z - не трогать оригиналы (зашифрованные файлы получат расширение .orz)"
    echo "   -x - заменить оригиналы (по умолчанию)"
    echo "   -c - обнаруживать скрытые папки (по умолчанию выкл.)"
    echo;
    echo "Общая справка по программному обеспечению GNU: <http://www.gnu.org/gethelp/>"
    echo "Сделал Буренков Игорь (Alrott SlimRG)";
    exit 0; #Все норм - пацан справку посмотрел
   else
    if [[ ${TEMP:0:1} = "r" ]]; then
     R=1;
     TEMP=${TEMP:1:${#TEMP}};
    else
     if [[ ${TEMP:0:1} = "t" ]]; then
      TEXD='Z*.txt';
      TEMP=${TEMP:1:${#TEMP}};
     else
      if [[ ${TEMP:0:1} = "x" ]]; then
       if [[ $E != 0 ]]; then echo "Выбраны несовместимые ключи!"; exit 610; fi; #От греха подальше 
       E=0;
       TEMP=${TEMP:1:${#TEMP}};
      else
       if [[ ${TEMP:0:1} = "z" ]]; then
        if [[ $E != 0 && $E != 1 ]]; then echo "Выбраны несовместимые ключи!"; exit 610; fi; #От греха подальше 
        E=1;
        TEMP=${TEMP:1:${#TEMP}};
       else
        if [[ ${TEMP:0:1} = "c" ]]; then
         SECF=1;
         TEMP=${TEMP:1:${#TEMP}};
        else
         if [[ ${TEMP:0:1} = "e" ]]; then
          if [[ $E != 0 && $E != 2 ]]; then echo "Выбраны несовместимые ключи!"; exit 610; fi;#От греха подальше 
          E=2;
          TEMP=${TEMP:1:${#TEMP}};
         else
          if [[ ${TEMP:0:1} = "s" ]]; then
           TEMP=${TEMP:1:${#TEMP}};
           S="";
           while [[ "${TEMP:0:1}" = "-" || "${TEMP:0:1}" = "0" || "${TEMP:0:1}" = "1" || "${TEMP:0:1}" = "2" || "${TEMP:0:1}" = "3" || "${TEMP:0:1}" = "4" || "${TEMP:0:1}" = "5" || "${TEMP:0:1}" = "6" || "${TEMP:0:1}" = "7" || "${TEMP:0:1}" = "8" || "${TEMP:0:1}" = "9" ]]; do
            S="$S${TEMP:0:1}";
            TEMP=${TEMP:1:${#TEMP}};
           done;
           if [[ $S = "" || $S = "-" ]]; then
            echo "Вы неверно указали длину";
            exit 1012;
           fi;
          else
           echo "Вы неправильно указали ключ";
           exit 325;
          fi;      
         fi;
        fi;
       fi;
      fi;
     fi;
    fi;
   fi;
  done;  
 else
  if [[ ${1:0:1} = '/' ]]; then   #Реагирование на адресс
   DIR="$DIR $1";
  else
   if [[ ${1:0:1} = '.' && ${1:1:2} != "" ]]; then
    if [[ ${TEXD:0:1} != 'Z'  ]]; then #В случае ключа -t - ненадо других расширений
     if [[ $TEXD = "" ]]; then
      TEXD='-name *'$1;  #Первое расширение
     else 
      TEXD=$TEXD' -o -name *'$1; #Второе расширение
     fi;
     if [[ "$SECF" = "1" ]]; then TEXD=$TEXD' -o -name .*'$1; fi; #Ищем скрытые файлы, если -с
    fi;
   else
    echo "Вы неправильно указали ключ или путь";
    exit 326;
   fi;
  fi; 
 fi;
 shift;
done;
if [[ "$DIR" = "" ]]; then echo "Вы не указали ни одной директории"; exit 328; fi; #не указана директория
if [[ "${TEXD:0:1}" = "Z"  ]]; then TEXD=' -name '${TEXD:1:${#TEXD}}; fi; #Преобразование при -t

#Найдем настоящее смещение
if (( $S < 0 )); then INVERSION="1"; S=${S:1:${#S}}; else INVERSION="0";  fi; 
S=$(( $S % 164 ));
if [[ $INVERSION = "1" ]]; then S="-"$S; fi;


#После этого приступаем к получению адрессов всех файлов
if [[ "$R" = "0" ]]; then R='-maxdepth 1'; else R=''; fi; #Реакция на ключ -r
if [[ "$SECF" = "1" ]]; then RECURS=''; else RECURS=' -not -name ".*"'; fi;
TICKERTYTU="0";
find "$DIR" $R -type f $TEXD $RECURS | while read FILES; do 
    if [[ "$TICKERTYTU" ==  "0" && "$FILES" == "" ]]; then echo "Не найдено файлов для конвертации"; else TICKERTYTU="1"; exit 0; fi;

   #Если включено сделать копию оригинала (-e)
   if [[ "$E" = "2" ]]; then  
    KAST="${FILES} ${FILES}.or"
    cp $KAST;
    fi;
   
   #Здесь приводим символы к нормальному виду
   
   TEMP=$(cat "${FILES}");
   TEMP2="";
   #Если ключ -z
   if [[ "$E" = "1" ]]; then PREFIX='.orz'; else PREFIX=''; fi;

   #Приводим другие тексты к нормализов. виду
   
   for ((k=0; k < ${#TEMP}; k++));do
   N="";
    case ${TEMP:$k:1} in
     #Английский алфавит
     'A') N='0'  ;;  'B') N='1'  ;;  'C') N='2'  ;;  'D') N='3'  ;;  'E') N='4'  ;;  'F') N='5'  ;;  'G') N='6'  ;;  'H') N='7'  ;;   
     'I') N='8'  ;;  'J') N='9'  ;;  'K') N='10' ;;  'L') N='11' ;;  'M') N='12' ;;  'N') N='13' ;;  'O') N='14' ;;  'P') N='15' ;;   
     'Q') N='16' ;;  'R') N='17' ;;  'S') N='18' ;;  'T') N='19' ;;  'U') N='20' ;;  'V') N='21' ;;  'W') N='22' ;;  'X') N='23' ;;   
     'Y') N='24' ;;  'Z') N='25' ;;
     
     'a') N='26' ;;  'b') N='27' ;;  'c') N='28' ;;  'd') N='29' ;;  'e') N='30' ;;  'f') N='31' ;;  'g') N='32' ;;  'h') N='33' ;; 
     'i') N='34' ;;  'j') N='35' ;;  'k') N='36' ;;  'l') N='37' ;;  'm') N='38' ;;  'n') N='39' ;;  'o') N='40' ;;  'p') N='41' ;;   
     'q') N='42' ;;  'r') N='43' ;;  's') N='44' ;;  't') N='45' ;;  'u') N='46' ;;  'v') N='47' ;;  'w') N='48' ;;  'x') N='49' ;;   
     'y') N='50' ;;  'z') N='51' ;; 
     
     #Русский алфавит
     'А') N='52' ;;  'Б') N='53' ;;  'В') N='54' ;;  'Г') N='55' ;;  'Д') N='56' ;;  'Е') N='57' ;;  'Ё') N='58' ;;  'Ж') N='59' ;;   
     'З') N='60' ;;  'И') N='61' ;;  'Й') N='62' ;;  'К') N='63' ;;  'Л') N='64' ;;  'М') N='65' ;;  'Н') N='66' ;;  'О') N='67' ;;   
     'П') N='68' ;;  'Р') N='69' ;;  'С') N='70' ;;  'Т') N='71' ;;  'У') N='72' ;;  'Ф') N='73' ;;  'Х') N='74' ;;  'Ц') N='75' ;;   
     'Ч') N='76' ;;  'Ш') N='77' ;;  'Щ') N='78' ;;  'Ъ') N='79' ;;  'Ы') N='80' ;;  'Ь') N='81' ;;  'Э') N='82' ;;  'Ю') N='83' ;;   
     'Я') N='84' ;; 
      
     'а') N='85'  ;;  'б') N='86'  ;;  'в') N='87'  ;;  'г') N='88'  ;;  'д') N='89'  ;;  'е') N='90'  ;;  'ё') N='91'  ;;  'ж') N='92'  ;;   
     'з') N='93'  ;;  'и') N='94'  ;;  'й') N='95'  ;;  'к') N='96'  ;;  'л') N='97'  ;;  'м') N='98'  ;;  'н') N='99'  ;;  'о') N='100' ;;   
     'п') N='101' ;;  'р') N='102' ;;  'с') N='103' ;;  'т') N='104' ;;  'у') N='105' ;;  'ф') N='106' ;;  'х') N='107' ;;  'ц') N='108' ;;   
     'ч') N='109' ;;  'ш') N='110' ;;  'щ') N='111' ;;  'ъ') N='112' ;;  'ы') N='113' ;;  'ь') N='114' ;;  'э') N='115' ;;  'ю') N='116' ;;   
     'я') N='117' ;; 
     
     #Прочие символы
     "'") N='118' ;; 
     '[') N='119' ;;  ']') N='120' ;;  '(') N='121' ;;  ')') N='122' ;;  '{') N='123' ;;  '}') N='124' ;;  '<') N='125' ;;  '>') N='126' ;;  
     ':') N='127' ;;  ',') N='128' ;;  '®') N='129' ;;  '!') N='130' ;;  '.') N='131' ;;  '-') N='132' ;;
     '?') N='133' ;;  '"') N='134' ;;  '«') N='135' ;;  '»') N='136' ;;
     ';') N='137' ;;  '/') N='138' ;;  ' ') N='139' ;;
    '+') N='140' ;;  '&') N='141' ;;  '₽') N='142' ;;  '@') N='143' ;;
     '*') N='144' ;;  '\') N='145' ;;  '^') N='146' ;;  '°') N='147' ;;  '#') N='148' ;; 
     '№') N='149' ;;  '%') N='150' ;;  '~') N='151' ;;  '_') N='152' ;;  '|') N='153' ;;
     
     #Цифры
     '1') N='154'  ;;  '2') N='155'  ;;  '3') N='156'  ;;  '4') N='157'  ;;  '5') N='158'  ;;  '6') N='159'  ;;  '7') N='160'  ;;  '8') N='161'  ;;   
     '9') N='162'  ;;  '0') N='163'  ;;  
     
     *) N='OTHER';; 
    esac;
    
     if [[ "$N" != 'OTHER' ]]; then
      N=$(( $N + $S )); #Применяем сдвиг и нормализуем
      if (( $N > 163 )); then N=$(( $N - 164 )); fi;
      if (( $N < 0 )); then N=$(( $N + 164 )); fi;
     fi;
     
     case $N in
      #Английский алфавит
      '0')  TEMP2="$TEMP2"'A';;  '1')  TEMP2="$TEMP2"'B';;  '2')  TEMP2="$TEMP2"'C';;  '3')  TEMP2="$TEMP2"'D';;  '4')  TEMP2="$TEMP2"'E';;  
      '5')  TEMP2="$TEMP2"'F';;  '6')  TEMP2="$TEMP2"'G';;  '7')  TEMP2="$TEMP2"'H';;  '8')  TEMP2="$TEMP2"'I';;  '9')  TEMP2="$TEMP2"'J';;
      '10') TEMP2="$TEMP2"'K';;  '11') TEMP2="$TEMP2"'L';;  '12') TEMP2="$TEMP2"'M';;  '13') TEMP2="$TEMP2"'N';;  '14') TEMP2="$TEMP2"'O';;
      '15') TEMP2="$TEMP2"'P';;  '16') TEMP2="$TEMP2"'Q';;  '17') TEMP2="$TEMP2"'R';;  '18') TEMP2="$TEMP2"'S';;  '19') TEMP2="$TEMP2"'T';;
      '20') TEMP2="$TEMP2"'U';;  '21') TEMP2="$TEMP2"'V';;  '22') TEMP2="$TEMP2"'W';;  '23') TEMP2="$TEMP2"'X';;  '24') TEMP2="$TEMP2"'Y';;
      '25') TEMP2="$TEMP2"'Z';; 
      
      '26') TEMP2="$TEMP2"'a';;  '27') TEMP2="$TEMP2"'b';;  '28') TEMP2="$TEMP2"'c';;  '29') TEMP2="$TEMP2"'d';;  '30') TEMP2="$TEMP2"'e';;
      '31') TEMP2="$TEMP2"'f';;  '32') TEMP2="$TEMP2"'g';;  '33') TEMP2="$TEMP2"'h';;  '34') TEMP2="$TEMP2"'i';;  '35') TEMP2="$TEMP2"'j';;
      '36') TEMP2="$TEMP2"'k';;  '37') TEMP2="$TEMP2"'l';;  '38') TEMP2="$TEMP2"'m';;  '39') TEMP2="$TEMP2"'n';;  '40') TEMP2="$TEMP2"'o';;
      '41') TEMP2="$TEMP2"'p';;  '42') TEMP2="$TEMP2"'q';;  '43') TEMP2="$TEMP2"'r';;  '44') TEMP2="$TEMP2"'s';;  '45') TEMP2="$TEMP2"'t';;
      '46') TEMP2="$TEMP2"'u';;  '47') TEMP2="$TEMP2"'v';;  '48') TEMP2="$TEMP2"'w';;  '49') TEMP2="$TEMP2"'x';;  '50') TEMP2="$TEMP2"'y';;
      '51') TEMP2="$TEMP2"'z';;
      
      #Русский алфавит
      '52') TEMP2="$TEMP2"'А';;  '53') TEMP2="$TEMP2"'Б';;  '54') TEMP2="$TEMP2"'В';;  '55') TEMP2="$TEMP2"'Г';;  '56') TEMP2="$TEMP2"'Д';;
      '57') TEMP2="$TEMP2"'Е';;  '58') TEMP2="$TEMP2"'Ё';;  '59') TEMP2="$TEMP2"'Ж';;  '60') TEMP2="$TEMP2"'З';;  '61') TEMP2="$TEMP2"'И';;
      '62') TEMP2="$TEMP2"'Й';;  '63') TEMP2="$TEMP2"'К';;  '64') TEMP2="$TEMP2"'Л';;  '65') TEMP2="$TEMP2"'М';;  '66') TEMP2="$TEMP2"'Н';;
      '67') TEMP2="$TEMP2"'О';;  '68') TEMP2="$TEMP2"'П';;  '69') TEMP2="$TEMP2"'Р';;  '70') TEMP2="$TEMP2"'С';;  '71') TEMP2="$TEMP2"'Т';;
      '72') TEMP2="$TEMP2"'У';;  '73') TEMP2="$TEMP2"'Ф';;  '74') TEMP2="$TEMP2"'Х';;  '75') TEMP2="$TEMP2"'Ц';;  '76') TEMP2="$TEMP2"'Ч';;
      '77') TEMP2="$TEMP2"'Ш';;  '78') TEMP2="$TEMP2"'Щ';;  '79') TEMP2="$TEMP2"'Ъ';;  '80') TEMP2="$TEMP2"'Ы';;  '81') TEMP2="$TEMP2"'Ь';;
      '82') TEMP2="$TEMP2"'Э';;  '83') TEMP2="$TEMP2"'Ю';;  '84') TEMP2="$TEMP2"'Я';;
      
      '85')  TEMP2="$TEMP2"'а';;  '86')  TEMP2="$TEMP2"'б';;  '87')  TEMP2="$TEMP2"'в';;  '88')  TEMP2="$TEMP2"'г';;  '89')  TEMP2="$TEMP2"'д';;
      '90')  TEMP2="$TEMP2"'е';;  '91')  TEMP2="$TEMP2"'ё';;  '92')  TEMP2="$TEMP2"'ж';;  '93')  TEMP2="$TEMP2"'з';;  '94')  TEMP2="$TEMP2"'и';;
      '95')  TEMP2="$TEMP2"'й';;  '96')  TEMP2="$TEMP2"'к';;  '97')  TEMP2="$TEMP2"'л';;  '98')  TEMP2="$TEMP2"'м';;  '99')  TEMP2="$TEMP2"'н';;
      '100') TEMP2="$TEMP2"'о';;  '101') TEMP2="$TEMP2"'п';;  '102') TEMP2="$TEMP2"'р';;  '103') TEMP2="$TEMP2"'с';;  '104') TEMP2="$TEMP2"'т';;
      '105') TEMP2="$TEMP2"'у';;  '106') TEMP2="$TEMP2"'ф';;  '107') TEMP2="$TEMP2"'х';;  '108') TEMP2="$TEMP2"'ц';;  '109') TEMP2="$TEMP2"'ч';;
      '110') TEMP2="$TEMP2"'ш';;  '111') TEMP2="$TEMP2"'щ';;  '112') TEMP2="$TEMP2"'ъ';;  '113') TEMP2="$TEMP2"'ы';;  '114') TEMP2="$TEMP2"'ь';;
      '115') TEMP2="$TEMP2"'э';;  '116') TEMP2="$TEMP2"'ю';;  '117') TEMP2="$TEMP2"'я';; 
      
      #Другие символы
      '118') TEMP2="$TEMP2""'";; 
      '119') TEMP2="$TEMP2"'[';;  '120') TEMP2="$TEMP2"']';;  '121') TEMP2="$TEMP2"'(';;  '122') TEMP2="$TEMP2"')';;
      '123') TEMP2="$TEMP2"'{';;  '124') TEMP2="$TEMP2"'}';;  '125') TEMP2="$TEMP2"'<';;  '126') TEMP2="$TEMP2"'>';;  '127') TEMP2="$TEMP2"':';;
      '128') TEMP2="$TEMP2"',';;  '129') TEMP2="$TEMP2"'®';;  '130') TEMP2="$TEMP2"'!';;  '131') TEMP2="$TEMP2"'.';;  '132') TEMP2="$TEMP2"'-';;
      '133') TEMP2="$TEMP2"'?';;  '134') TEMP2="$TEMP2"'"';;  '135') TEMP2="$TEMP2"'«';;  '136') TEMP2="$TEMP2"'»';;  '137') TEMP2="$TEMP2"';';;
      '138') TEMP2="$TEMP2"'/';;  '139') TEMP2="$TEMP2"' ';;  '140') TEMP2="$TEMP2"'+';;  '141') TEMP2="$TEMP2"'&';;  '142') TEMP2="$TEMP2"'₽';;
      '143') TEMP2="$TEMP2"'@';;  '144') TEMP2="$TEMP2"'*';;  '145') TEMP2="$TEMP2"'\';;  '146') TEMP2="$TEMP2"'^';;  '147') TEMP2="$TEMP2"'°';;
      '148') TEMP2="$TEMP2"'#';;  '149') TEMP2="$TEMP2"'№';;  '150') TEMP2="$TEMP2"'%';;  '151') TEMP2="$TEMP2"'~';;  '152') TEMP2="$TEMP2"'_';;
      '153') TEMP2="$TEMP2"'|';;  
      
      #Цифры
      '154') TEMP2="$TEMP2"'1';;  '155') TEMP2="$TEMP2"'2';;  '156') TEMP2="$TEMP2"'3';;  '157') TEMP2="$TEMP2"'4';;  '158') TEMP2="$TEMP2"'5';;
      '159') TEMP2="$TEMP2"'6';;  '160') TEMP2="$TEMP2"'7';;  '161') TEMP2="$TEMP2"'8';;  '162') TEMP2="$TEMP2"'9';;  '163') TEMP2="$TEMP2"'0';; 

      *) TEMP2="$TEMP2""${TEMP:$k:1}";;
     esac;
     
   done;
   echo "$TEMP2" > "${FILES}$PREFIX";
  done;

