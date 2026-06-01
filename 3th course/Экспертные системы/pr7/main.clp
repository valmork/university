;;; ЭКСПЕРТНАЯ СИСТЕМА ДИАГНОСТИКИ ЗАБОЛЕВАНИЙ (17 правил)

(deftemplate symptom
   (slot name)
   (slot value))

(deftemplate diagnosis
   (slot name))

;;; Функция опроса
(deffunction ask-question (?question ?allowed-values)
   (printout t ?question " (" ?allowed-values "): ")
   (bind ?answer (read))
   ;; В CLIPS используется lowcase вместо lowercase
   (if (lexemep ?answer) 
       then (bind ?answer (lowcase ?answer)))
   (while (not (member$ ?answer (create$ yes no y n да нет))) do
      (printout t "Пожалуйста, ответьте 'yes' или 'no': ")
      (bind ?answer (read))
      (if (lexemep ?answer) 
          then (bind ?answer (lowcase ?answer))))
   (if (member$ ?answer (create$ yes y да)) 
       then yes 
       else no))

;;; ПРАВИЛА СБОРА ДАННЫХ

;; 1. Начало работы
(defrule rule-1-start
   (declare (salience 100))
   =>
   (printout t "   Система первичной диагностики болезней  " crlf)
   (assert (symptom (name fever) (value (ask-question "У вас есть повышенная температура?" "yes/no")))))

;; 2. Опрос про кашель
(defrule rule-2-ask-cough
   (symptom (name fever) (value yes))
   (not (symptom (name cough)))
   =>
   (assert (symptom (name cough) (value (ask-question "У вас есть кашель?" "yes/no")))))

;; 3. Опрос про горло
(defrule rule-3-ask-throat
   (not (symptom (name throat-pain)))
   =>
   (assert (symptom (name throat-pain) (value (ask-question "У вас болит горло?" "yes/no")))))

;; 4. Опрос про насморк
(defrule rule-4-ask-runny-nose
   (not (symptom (name runny-nose)))
   =>
   (assert (symptom (name runny-nose) (value (ask-question "У вас есть насморк?" "yes/no")))))

;; 5. Опрос про головную боль
(defrule rule-5-ask-headache
   (not (symptom (name headache)))
   =>
   (assert (symptom (name headache) (value (ask-question "У вас болит голова?" "yes/no")))))

;; 6. Опрос про мышцы
(defrule rule-6-ask-muscle-pain
   (symptom (name fever) (value yes))
   (not (symptom (name muscle-pain)))
   =>
   (assert (symptom (name muscle-pain) (value (ask-question "Вы чувствуете ломоту в мышцах?" "yes/no")))))

;; 7. Опрос про одышку
(defrule rule-7-ask-short-breath
   (symptom (name cough) (value yes))
   (not (symptom (name short-breath)))
   =>
   (assert (symptom (name short-breath) (value (ask-question "У вас есть одышка?" "yes/no")))))

;; 8. Опрос про налет в горле
(defrule rule-8-ask-spots
   (symptom (name throat-pain) (value yes))
   (not (symptom (name white-spots)))
   =>
   (assert (symptom (name white-spots) (value (ask-question "Видны ли белые пятна на миндалинах?" "yes/no")))))

;; 9. Опрос про тошноту
(defrule rule-9-ask-nausea
   (not (symptom (name nausea)))
   =>
   (assert (symptom (name nausea) (value (ask-question "У вас есть тошнота или боли в животе?" "yes/no")))))

;;; ПРАВИЛА ЛОГИЧЕСКОГО ВЫВОДА (ДИАГНОЗЫ)

;; 10. Правило для Гриппа
(defrule rule-10-diag-flu
   (symptom (name fever) (value yes))
   (symptom (name headache) (value yes))
   (symptom (name muscle-pain) (value yes))
   =>
   (assert (diagnosis (name "Грипп"))))

;; 11. Правило для ОРВИ
(defrule rule-11-diag-cold
   (symptom (name runny-nose) (value yes))
   (symptom (name throat-pain) (value yes))
   (symptom (name fever) (value no))
   =>
   (assert (diagnosis (name "ОРВИ (Простуда)"))))

;; 12. Правило для Ангины
(defrule rule-12-diag-angina
   (symptom (name throat-pain) (value yes))
   (symptom (name white-spots) (value yes))
   (symptom (name fever) (value yes))
   =>
   (assert (diagnosis (name "Ангина (Тонзиллит)"))))

;; 13. Правило для Пневмонии
(defrule rule-13-diag-pneumonia
   (symptom (name fever) (value yes))
   (symptom (name cough) (value yes))
   (symptom (name short-breath) (value yes))
   =>
   (assert (diagnosis (name "Пневмония"))))

;; 14. Правило для Аллергии
(defrule rule-14-diag-allergy
   (symptom (name runny-nose) (value yes))
   (symptom (name fever) (value no))
   (symptom (name throat-pain) (value no))
   =>
   (assert (diagnosis (name "Аллергический ринит"))))

;; 15. Правило для Гастрита
(defrule rule-15-diag-gastritis
   (symptom (name nausea) (value yes))
   (symptom (name fever) (value no))
   =>
   (assert (diagnosis (name "Гастрит"))))

;; 16. Правило для Инфекции
(defrule rule-16-diag-infection
   (symptom (name nausea) (value yes))
   (symptom (name fever) (value yes))
   =>
   (assert (diagnosis (name "Кишечная инфекция"))))

;; ВЫВОД РЕЗУЛЬТАТА 

;; Заключительный отчет
(defrule rule-17-report
   (declare (salience 0))
   (diagnosis (name ?name))
   =>
   (printout t "РЕЗУЛЬТАТ: Подозрение на " ?name crlf)
   (printout t "Обратитесь к врачу для подтверждения диагноза." crlf)
   (halt)
)

;; Дополнительное правило на случай, если ничего не найдено
(defrule rule-none
   (declare (salience -1))
   (not (diagnosis (name ?)))
   =>
   (printout t crlf "Диагноз не определен. Рекомендуется визит к врачу." crlf))