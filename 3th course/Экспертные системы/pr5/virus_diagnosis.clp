(deffunction ask-question (?question $?allowed-values)
  (printout t ?question)
  (bind ?answer (read))
  (if (lexemep ?answer) then (bind ?answer (lowcase ?answer)))
  (while (not (member$ ?answer ?allowed-values)) do
    (printout t ?question)
    (bind ?answer (read))
    (if (lexemep ?answer) then (bind ?answer (lowcase ?answer)))
  )
  ?answer
)

(deffunction yes-or-no-p (?question)
  (bind ?response (ask-question ?question yes no y n))
  (if (or (eq ?response yes) (eq ?response y)) then TRUE else FALSE)
)

(deftemplate diagnosis
  (slot description)
)

(deffacts initial-facts
  (diagnosis-done no)
  (exit no)
)

(defrule start-diagnosis
  (declare (salience 20)) 
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (exit yes))
  =>
  (printout t "ЭКСПЕРТНАЯ СИСТЕМА ОБНАРУЖЕНИЯ ВИРУСОВ" crlf)
  (printout t crlf "Отвечайте 'yes' или 'no' на каждый вопрос." crlf crlf)
)

;; СБОР СИМПТОМОВ (ВИРУСЫ)

(defrule file-virus-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (file-checked))
  =>
  (if (yes-or-no-p "Изменились ли даты и размеры исполняемых файлов (EXE, COM)? (yes/no) ")
    then
      (assert (file-size-changed))
      (assert (file-checked))
    else
      (assert (file-ok))
      (assert (file-checked))
  )
)

(defrule boot-virus-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (boot-checked))
  =>
  (if (yes-or-no-p "Компьютер не загружается с жёсткого диска, но загружается с дискеты? (yes/no) ")
    then
      (assert (boot-fail))
      (assert (boot-checked))
    else
      (assert (boot-ok))
      (assert (boot-checked))
  )
)

(defrule macro-virus-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (macro-checked))
  =>
  (if (yes-or-no-p "Документы Office (Word, Excel) ведут себя странно (изменяют текст, запрашивают пароль)? (yes/no) ")
    then
      (assert (macro-suspect))
      (assert (macro-checked))
    else
      (assert (macro-ok))
      (assert (macro-checked))
  )
)

(defrule script-virus-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (script-checked))
  =>
  (if (yes-or-no-p "Появляются всплывающие окна с рекламой или угрозами при открытии веб-страниц? (yes/no) ")
    then
      (assert (script-suspect))
      (assert (script-checked))
    else
      (assert (script-ok))
      (assert (script-checked))
  )
)

(defrule worm-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (worm-checked))
  =>
  (if (yes-or-no-p "Компьютер сильно тормозит, интернет трафик аномально высок? (yes/no) ")
    then
      (assert (worm-suspect))
      (assert (worm-checked))
    else
      (assert (worm-ok))
      (assert (worm-checked))
  )
)

(defrule trojan-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (trojan-checked))
  =>
  (if (yes-or-no-p "Появляются неизвестные программы в автозагрузке, антивирус отключён сам собой? (yes/no) ")
    then
      (assert (trojan-suspect))
      (assert (trojan-checked))
    else
      (assert (trojan-ok))
      (assert (trojan-checked))
  )
)

(defrule ransomware-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (ransom-checked))
  =>
  (if (yes-or-no-p "Файлы на диске переименованы или не открываются, появилась записка с требованием выкупа? (yes/no) ")
    then
      (assert (ransom-suspect))
      (assert (ransom-checked))
    else
      (assert (ransom-ok))
      (assert (ransom-checked))
  )
)

(defrule keylogger-symptoms
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (keylog-checked))
  =>
  (if (yes-or-no-p "Наблюдается необъяснимая активность в интернете (перехват паролей, странные входы в соцсети)? (yes/no) ")
    then
      (assert (keylog-suspect))
      (assert (keylog-checked))
    else
      (assert (keylog-ok))
      (assert (keylog-checked))
  )
)

(defrule antivirus-disabled
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (av-checked))
  =>
  (if (yes-or-no-p "Антивирусная программа отключена и не запускается? (yes/no) ")
    then
      (assert (av-disabled))
      (assert (av-checked))
    else
      (assert (av-ok))
      (assert (av-checked))
  )
)

;; ДИАГНОСТИЧЕСКИЕ ПРАВИЛА (ЛЕЧЕНИЕ)

(defrule diagnose-file-virus
  (declare (salience 10))
  (file-size-changed)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен файловый вирус. Вирус изменяет код исполняемых файлов. Рекомендация: запустить антивирусную проверку, восстановить файлы из резервной копии.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-boot-virus
  (declare (salience 10))
  (boot-fail)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен загрузочный вирус (boot-вирус). Вирус поражает загрузочный сектор диска. Рекомендация: загрузиться с антивирусного диска и восстановить загрузочную запись.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-macro-virus
  (declare (salience 10))
  (macro-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен макровирус (поражает документы Office). Рекомендация: открыть документы в безопасном режиме, отключить макросы, проверить антивирусом.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-script-virus
  (declare (salience 10))
  (script-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен скриптовый вирус или рекламное ПО (adware). Рекомендация: очистить кэш браузера, проверить расширения, запустить антивирус.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-worm
  (declare (salience 10))
  (worm-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен сетевой червь (worm). Вирус распространяется по сети, вызывая перегрузку трафика. Рекомендация: отключить компьютер от сети, провести полное сканирование.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-trojan
  (declare (salience 10))
  (trojan-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен троян (троянская программа). Маскируется под полезное ПО, может воровать данные. Рекомендация: проверить автозагрузку, удалить подозрительные программы, сменить пароли.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-ransomware
  (declare (salience 10))
  (ransom-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен вирус-шифровальщик (ransomware). Файлы зашифрованы. НЕ платите выкуп! Рекомендация: изолировать компьютер, попробовать дешифраторы с сайтов antivirus, восстановить из бэкапов.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-keylogger
  (declare (salience 10))
  (keylog-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Обнаружен кейлоггер (шпионское ПО для перехвата нажатий клавиш). Рекомендация: проверить систему антивирусом и антишпионом, сменить все пароли.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule diagnose-av-disabled
  (declare (salience 10))
  (av-disabled)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Вероятно, активен вирус, отключающий антивирус (троян или руткит). Рекомендация: загрузиться в безопасном режиме, запустить лечащую утилиту (например, Dr.Web CureIt).")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

(defrule generic-slow-and-changes
  (declare (salience 9))
  (or (file-size-changed) (macro-suspect))
  (worm-suspect)
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (assert (diagnosis (description "Высокая вероятность присутствия вируса общего типа (возможно, смешанный файлово-сетевой вирус). Рекомендуется глубокая проверка антивирусом с актуальными базами.")))
  (assert (diagnosis-done yes))
  (assert (exit yes))
)

;; ПРАВИЛА ОТСУТСТВИЯ ВИРУСА И ВЫВОДА

(defrule all-questions-answered
  (declare (salience 1))
  (file-checked)
  (boot-checked)
  (macro-checked)
  (script-checked)
  (worm-checked)
  (trojan-checked)
  (ransom-checked)
  (keylog-checked)
  (av-checked)
  (not (diagnosis))
  (not (diagnosis-done yes))
  (not (all-done))          
  =>
  (assert (all-done))
)

(defrule no-virus-found
  (declare (salience 5))
  (all-done)                
  (not (diagnosis))
  (not (diagnosis-done yes))
  =>
  (printout t "По имеющимся симптомам не удалось идентифицировать вирус." crlf)
  (printout t "Возможно, проблема вызвана сбоем оборудования или программным конфликтом." crlf)
  (assert (exit yes))
  (assert (diagnosis-done yes))
)

(defrule print-diagnosis
  (declare (salience 10)) 
  (diagnosis (description ?text))
  =>
  (printout t "РЕЗУЛЬТАТ ДИАГНОСТИКИ:" crlf)
  (printout t ?text crlf)
  (printout t crlf "Рекомендуется дополнительно обновить антивирусные базы и выполнить полное сканирование." crlf)
  (assert (exit yes))
)