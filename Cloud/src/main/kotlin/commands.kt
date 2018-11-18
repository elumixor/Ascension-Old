/**
 * Business logic testing
 */

fun main(args: Array<String>) {
    do {
        val line = (readLine() ?: "").split(' ')
        val arg = if (line.size > 1) line[1] else ""

        when (line[0].toLowerCase()) {
            "create" -> {
                val obj = arg.split(' ')[0].toLowerCase()
                when (obj) {
                    "goal" -> println("New goal created")
                    else -> println("Cannot create $obj")
                }
            }
            "exit" -> return
            else -> println("No such command: ${line[0]}")
        }
    } while (true)
}

