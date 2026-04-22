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
  (repair-done no)
  (exit no)
)

(defrule power-supply-failure
  (not (diagnosis))
  (not (repair-done yes))
  (not (power-checked))
  =>
  (if (not (yes-or-no-p "Компьютер не включается? (yes/no) "))
    then
      (assert (power-works))
      (assert (power-checked))
    else
      (if (yes-or-no-p "Слышны щелчки или запах гари? (yes/no) ")
        then
          (assert (diagnosis (description "Неисправен блок питания.")))
          (assert (repair-done yes))
          (assert (exit yes))
        else
          (assert (power-no-sign))
          (assert (power-checked))
      )
  )
)

(defrule motherboard-failure
  (power-no-sign)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (if (yes-or-no-p "Материнская плата получает дежурное напряжение (светодиоды горят)? (yes/no) ")
    then
      (assert (diagnosis (description "Проблема с цепями питания материнской платы.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (no-power-at-all))
  )
)

(defrule no-power-at-all-diagnosis
  (declare (salience 20))
  (no-power-at-all)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (assert (diagnosis (description "Полное отсутствие питания. Проверьте кабель питания, розетку, сетевой фильтр. Если всё исправно — неисправен блок питания.")))
  (assert (repair-done yes))
  (assert (exit yes))
)

(defrule no-image
  (power-works)
  (not (diagnosis))
  (not (repair-done yes))
  (not (image-checked))
  =>
  (if (yes-or-no-p "Компьютер включается, но нет изображения на экране? (yes/no) ")
    then
      (if (yes-or-no-p "При подключении к другому монитору изображение появляется? (yes/no) ")
        then
          (assert (diagnosis (description "Неисправен монитор или кабель.")))
          (assert (repair-done yes))
          (assert (exit yes))
        else
          (assert (gpu-suspect))
      )
      (assert (image-checked))
    else
      (assert (image-ok))
      (assert (image-checked))
  )
)

(defrule gpu-failure
  (gpu-suspect)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (if (yes-or-no-p "При включении слышны один длинный и два коротких сигнала? (yes/no) ")
    then
      (assert (diagnosis (description "Видеокарта неисправна или плохо контактирует.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (diagnosis (description "Возможна неисправность ОЗУ или материнской платы.")))
      (assert (repair-done yes))
      (assert (exit yes))
  )
)

(defrule ram-failure
  (image-ok)
  (not (diagnosis))
  (not (repair-done yes))
  (not (ram-checked))
  =>
  (if (yes-or-no-p "Случайные перезагрузки или синий экран смерти? (yes/no) ")
    then
      (if (yes-or-no-p "Ошибки возникают случайным образом? (yes/no) ")
        then
          (assert (diagnosis (description "Неисправна оперативная память (ОЗУ). Запустите MemTest86.")))
          (assert (repair-done yes))
          (assert (exit yes))
        else
          (assert (sw-suspect))
      )
      (assert (ram-checked))
    else
      (assert (ram-stable))
      (assert (ram-checked))
  )
)

(defrule hdd-failure
  (ram-stable)
  (not (diagnosis))
  (not (repair-done yes))
  (not (hdd-checked))
  =>
  (if (yes-or-no-p "Медленная загрузка, щелчки или скрежет? (yes/no) ")
    then
      (assert (diagnosis (description "Неисправен жесткий диск (HDD) или SSD. Сделайте резервную копию.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (hdd-ok))
      (assert (hdd-checked))
  )
)
(defrule overheating
  (hdd-ok)
  (not (diagnosis))
  (not (repair-done yes))
  (not (temp-checked))
  =>
  (if (yes-or-no-p "Компьютер выключается под нагрузкой (игры, рендеринг)? (yes/no) ")
    then
      (if (yes-or-no-p "Кулеры работают на максимуме, корпус горячий? (yes/no) ")
        then
          (assert (diagnosis (description "Перегрев. Очистите кулеры, замените термопасту.")))
          (assert (repair-done yes))
          (assert (exit yes))
        else
          (assert (psu-overheat))
      )
      (assert (temp-checked))
    else
      (assert (temp-normal))
      (assert (temp-checked))
  )
)

(defrule psu-overload
  (psu-overheat)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (if (yes-or-no-p "Выключается под нагрузкой, но после остывания работает? (yes/no) ")
    then
      (assert (diagnosis (description "Блок питания не выдерживает нагрузку (перегрузка или недостаточная мощность).")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (diagnosis (description "Проблема с материнской платой или процессором.")))
      (assert (repair-done yes))
      (assert (exit yes))
  )
)

(defrule software-issue
  (temp-normal)
  (not (diagnosis))
  (not (repair-done yes))
  (not (sw-checked))
  =>
  (if (yes-or-no-p "Медленная работа, программы зависают, но аппаратные тесты проходят? (yes/no) ")
    then
      (if (yes-or-no-p "Недавно устанавливали новое ПО или обновления? (yes/no) ")
        then
          (assert (diagnosis (description "Конфликт программного обеспечения, драйверов или вирусы.")))
          (assert (repair-done yes))
          (assert (exit yes))
        else
          (assert (virus-suspect))
      )
      (assert (sw-checked))
    else
      (assert (sw-clean))
      (assert (sw-checked))
  )
)

(defrule virus-infection
  (virus-suspect)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (if (yes-or-no-p "Всплывающие окна, перенаправления в браузере, антивирус отключён? (yes/no) ")
    then
      (assert (diagnosis (description "Заражение вредоносным ПО. Запустите антивирусную проверку.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (diagnosis (description "Рекомендуется переустановка ОС или восстановление из образа.")))
      (assert (repair-done yes))
      (assert (exit yes))
  )
)

(defrule driver-conflict
  (sw-clean)
  (not (diagnosis))
  (not (repair-done yes))
  =>
  (if (yes-or-no-p "Некоторые устройства (принтер, USB-мышь) перестали работать после обновления? (yes/no) ")
    then
      (assert (diagnosis (description "Конфликт драйверов. Откатите драйверы.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (diagnosis (description "Явных аппаратных неисправностей не найдено. Проверьте журнал событий Windows.")))
      (assert (repair-done yes))
      (assert (exit yes))
  )
)

(defrule fan-failure
  (not (diagnosis))
  (not (repair-done yes))
  (not (fan-checked))
  =>
  (if (yes-or-no-p "Сильный гул, треск или вибрация от кулеров? (yes/no) ")
    then
      (assert (diagnosis (description "Неисправен подшипник вентилятора. Замените вентилятор.")))
      (assert (repair-done yes))
      (assert (exit yes))
    else
      (assert (fan-ok))
      (assert (fan-checked))
  )
)

(defrule print-diagnosis
  (declare (salience 10))
  (diagnosis (description ?text))
  =>
  (printout t "РЕЗУЛЬТАТ ДИАГНОСТИКИ:" crlf)
  (printout t ?text crlf)
  (printout t crlf "Рекомендация: обратитесь к специалисту или выполните указанные действия." crlf)
  (assert (exit yes))
)

(defrule no-diagnosis-found
  (declare (salience 5))
  (not (diagnosis))
  (not (repair-done yes))
  (exit no)
  =>
  (printout t crlf "Не удалось определить причину неисправности." crlf)
  (printout t "Попробуйте выполнить комплексную аппаратную диагностику." crlf)
  (assert (exit yes))
)
(defrule start-diagnosis
  (not (diagnosis))
  (not (repair-done yes))
  (not (exit yes))
  =>
  (printout t "*     ЭКСПЕРТНАЯ СИСТЕМА ДИАГНОСТИКИ ПК              *" crlf)
  (printout t crlf "Отвечайте 'yes' или 'no' на каждый вопрос." crlf crlf)
)