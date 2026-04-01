data class Rule(
    val id: String,
    val conditions: List<String>,
    val conclusion: String
)

data class InferenceStep(
    val stepNumber: Int,
    val workingMemory: Set<String>,
    val conflictSet: List<String>,
    val activatedRule: String
)

class ForwardChainingEngine(
    private val rules: List<Rule>
) {
    fun run(initialFacts: Set<String>): Pair<Set<String>, List<InferenceStep>> {
        val workingMemory = initialFacts.toMutableSet()
        val steps = mutableListOf<InferenceStep>()
        var stepNumber = 1
        var changed = true

        while (changed) {

            changed = false

            // Конфликтное множество - если все условия содержатся в рабочей памяти и заключение не в рабочей памяти,
            // то тогда правило попадает в конфликтное множество
            val conflictSet = rules.filter { rule ->
                rule.conditions.all { it in workingMemory } && rule.conclusion !in workingMemory
            }

            if (conflictSet.isEmpty()) break

            // Стратегия разрешения - по умолчанию выбирается первое правило
            val activated = conflictSet.last()

            // Записываем шаг до добавления нового факта
            steps.add(
                InferenceStep(
                    stepNumber = stepNumber++,
                    workingMemory = workingMemory.toSet(),
                    conflictSet = conflictSet.map { it.id },
                    activatedRule = activated.id
                )
            )

            // Добавляем новый факт после записи шага
            workingMemory.add(activated.conclusion)
            changed = true
        }

        // Если конфликтное множество пусто - остановка. Достаем пустое множество
        val finalConflict = rules.filter { rule ->
            rule.conditions.all { it in workingMemory } && rule.conclusion !in workingMemory
        }
        if (steps.isNotEmpty()) {
            steps.add(
                InferenceStep(
                    stepNumber = stepNumber,
                    workingMemory = workingMemory.toSet(),
                    conflictSet = finalConflict.map { it.id },
                    activatedRule = "Остановка"
                )
            )
        }

        return Pair(workingMemory, steps)
    }
}

fun printResultTable(
    initialFacts: Set<String>,
    steps: List<InferenceStep>,
    rules: List<Rule>
) {
    val colWidths = intArrayOf(8, 40, 25, 25)
    val headers = listOf("№ шага", "Рабочая память", "Конфликтное множество", "Активизированное правило")

    fun formatWithLineBreaks(facts: String): List<String> {
        val factList = facts.split(", ")
        if (factList.size <= 2) return listOf(facts)

        return factList.chunked(2).map { it.joinToString(", ") }
    }

    fun centerText(text: String, width: Int): String {
        if (text.length >= width) return text
        val padding = width - text.length
        val leftPad = padding / 2
        val rightPad = padding - leftPad
        return " ".repeat(leftPad) + text + " ".repeat(rightPad)
    }

    fun centerVertically(lines: List<String>, maxLines: Int, width: Int): List<String> {
        val result = mutableListOf<String>()
        val totalPadding = maxLines - lines.size
        val topPadding = totalPadding / 2
        val bottomPadding = totalPadding - topPadding

        repeat(topPadding) { result.add(" ".repeat(width)) }
        result.addAll(lines.map { centerText(it, width) })
        repeat(bottomPadding) { result.add(" ".repeat(width)) }

        return result
    }

    fun printRow(cells: List<Any>) {
        val stepNum = cells[0].toString()
        val memoryLines = formatWithLineBreaks(cells[1].toString())
        val conflict = cells[2].toString()
        val rule = cells[3].toString()

        val conflictLines = listOf(conflict)
        val ruleLines = listOf(rule)

        val maxLines = memoryLines.size

        val centeredConflict = centerVertically(conflictLines, maxLines, colWidths[2])
        val centeredRule = centerVertically(ruleLines, maxLines, colWidths[3])

        for (i in 0 until maxLines) {
            val stepCell = if (i == 0) stepNum.padEnd(colWidths[0]) else " ".padEnd(colWidths[0])
            val memoryCell = memoryLines[i].padEnd(colWidths[1])
            val conflictCell = centeredConflict[i]
            val ruleCell = centeredRule[i]

            println("$stepCell  $memoryCell  $conflictCell  $ruleCell")
        }
    }

    println("\nПРЯМОЙ ВЫВОД — РЕЗУЛЬТАТЫ РАБОТЫ")

    println("\nБАЗА ПРАВИЛ:")
    rules.forEach { r ->
        println("  ${r.id}: ${r.conditions.joinToString(" ∧ ")} → ${r.conclusion}")
    }

    println("\nТАБЛИЦА ШАГОВ ВЫВОДА:\n")

    // Печатаем заголовки
    println("${headers[0].padEnd(colWidths[0])}  ${headers[1].padEnd(colWidths[1])}  ${headers[2].padEnd(colWidths[2])}  ${headers[3].padEnd(colWidths[3])}")
    println("-".repeat(colWidths.sum() + colWidths.size * 2))

    // Нулевая строка
    printRow(listOf("0", initialFacts.sorted().joinToString(", "), "—", "—"))

    steps.forEach { step ->
        val conflict = if (step.conflictSet.isEmpty()) "—" else step.conflictSet.joinToString(", ")
        printRow(listOf(
            step.stepNumber.toString(),
            step.workingMemory.sorted().joinToString(", "),
            conflict,
            step.activatedRule
        ))
    }
}

fun main() {
    println("ПРИМЕР: Классификация животных")

    val rules1 = listOf(
        Rule("R1",  listOf("имеет_шерсть"),"млекопитающее"),
        Rule("R2",  listOf("кормит_молоком"),"млекопитающее"),
        Rule("R3",  listOf("имеет_перья"),"птица"),
        Rule("R4",  listOf("умеет_летать", "откладывает_яйца"),"птица"),
        Rule("R5",  listOf("млекопитающее", "ест_мясо"),"плотоядное"),
        Rule("R6",  listOf("млекопитающее", "имеет_когти", "зоркие_глаза"),"плотоядное"),
        Rule("R7",  listOf("млекопитающее", "копыта"),"парнокопытное"),
        Rule("R8",  listOf("плотоядное", "желтый_цвет", "пятна"),"гепард"),
        Rule("R9",  listOf("плотоядное", "желтый_цвет", "полосы"),"тигр"),
        Rule("R10", listOf("парнокопытное", "длинная_шея"),"жираф"),
        Rule("R11", listOf("парнокопытное", "полосы"),"зебра"),
    )

    val initialFacts1 = setOf(
        "имеет_шерсть", "ест_мясо", "желтый_цвет", "пятна", "зоркие_глаза", "имеет_когти"
    )

    val engine1 = ForwardChainingEngine(rules1)
    val (_, steps1) = engine1.run(initialFacts1)
    printResultTable(initialFacts1, steps1, rules1)
}