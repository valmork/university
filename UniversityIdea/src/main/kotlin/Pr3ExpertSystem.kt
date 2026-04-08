data class Rule(
    val id: String,
    val conditions: List<String>,
    val conclusion: String
)

data class InferenceStep(
    val stepNumber: Int,
    val workingMemory: List<String>,
    val trueFacts: Set<String>,
    val conflictSet: List<String>,
    val activatedRule: String
)

class BackwardChainingEngine(private val rules: List<Rule>) {

    fun run(goal: String, initialTrueFacts: Set<String>): List<InferenceStep> {
        val subgoals = mutableListOf(goal)
        val knownFacts = initialTrueFacts.toMutableSet()
        val activatedRules = mutableSetOf<String>()
        val steps = mutableListOf<InferenceStep>()

        var stepCount = 0

        while (goal !in knownFacts) {
            val conflictSet = mutableListOf<Rule>()
            for (subgoal in subgoals) {
                if (subgoal in knownFacts) continue
                val matches = rules.filter { it.conclusion == subgoal && it.id !in activatedRules }
                conflictSet.addAll(matches)
            }

            if (conflictSet.isEmpty()) break

            val activeRule = conflictSet.first()

            steps.add(InferenceStep(
                stepNumber = stepCount++,
                workingMemory = subgoals + initialFactsInOrder(knownFacts, initialTrueFacts),
                trueFacts = knownFacts.toSet(),
                conflictSet = conflictSet.map { it.id },
                activatedRule = activeRule.id
            ))

            activatedRules.add(activeRule.id)

            // Проверка, что факта нет в истинных и он еще не добавлен как подцель
            for (cond in activeRule.conditions) {
                if (cond !in knownFacts && cond !in subgoals) {
                    subgoals.add(cond)
                }
            }

            propagateTruth(knownFacts, activatedRules)
        }

        val finalConflict = mutableListOf<String>()
        for (subgoal in subgoals) {
            if (subgoal in knownFacts) continue
            finalConflict.addAll(rules.filter { it.conclusion == subgoal && it.id !in activatedRules }.map { it.id })
        }

        steps.add(InferenceStep(
            stepNumber = stepCount,
            workingMemory = subgoals + initialFactsInOrder(knownFacts, initialTrueFacts),
            trueFacts = knownFacts.toSet(),
            conflictSet = finalConflict,
            activatedRule = "Остановка"
        ))

        return steps
    }

    private fun initialFactsInOrder(currentTrue: Set<String>, initial: Set<String>): List<String> {
        // Возвращается L, M, N в алфавитном порядке
        return initial.sorted()
    }

    private fun propagateTruth(knownFacts: MutableSet<String>, activatedRules: Set<String>) {
        var added: Boolean
        do {
            added = false
            // Правило дает истинный вывод, если оно было активировано и все его посылки истинны
            for (rule in rules) {
                if (rule.id in activatedRules && rule.conclusion !in knownFacts) {
                    if (rule.conditions.all { it in knownFacts }) {
                        knownFacts.add(rule.conclusion)
                        added = true
                    }
                }
            }
        } while (added)
    }
}

fun printTable(steps: List<InferenceStep>) {
    val header = "| № шага | Рабочая память %-40s | Конфликтное множество | Актив. правило |".format("")
    val line = "-".repeat(110)
    println(line)
    println("| № шага | Рабочая память %-43s | Конфликт. множ-во | Активиз. правило |".format(""))
    println(line)

    for (step in steps) {
        val wmStr = step.workingMemory.joinToString(", ") {
            if (it in step.trueFacts) "$it*" else it
        }
        val conflictStr = if (step.conflictSet.isEmpty()) "—" else step.conflictSet.joinToString(", ")

        println("| %-6d | %-58s | %-17s | %-16s |".format(
            step.stepNumber, wmStr, conflictStr, step.activatedRule
        ))
    }
    println(line)
}

fun main() {
    val rules = listOf(
        Rule("1",  listOf("G", "H"), "C"),
        Rule("2",  listOf("I", "K"), "D"),
        Rule("3",  listOf("L", "M"), "E"),
        Rule("4",  listOf("N"),      "F"),
        Rule("5",  listOf("O"),      "F"),
        Rule("6",  listOf("C"),      "A"),
        Rule("7",  listOf("D"),      "A"),
        Rule("8",  listOf("E"),      "B"),
        Rule("9",  listOf("F"),      "B"),
        Rule("10", listOf("A"),      "Goal"),
        Rule("11", listOf("B"),      "Goal")
    )
    for (rule in rules) {
        println("${rule.id}.${rule.conditions} - ${rule.conclusion}")
    }

    val initialTrueFacts = setOf("L", "M", "N")
    val engine = BackwardChainingEngine(rules)
    val result = engine.run("Goal", initialTrueFacts)

    printTable(result)
}