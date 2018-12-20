/**
 * Business logic testing
 */

fun parse(line: String): Pair<String, String> {
    val split = line.split(' ')
    return Pair(split[0], if (split.size > 1) split.slice(1 until split.size).joinToString(separator = " ") else "")
}

fun parse(parsed: Pair<String, String>): Pair<String, String> {
    val split = parsed.second.split(' ')
    return Pair(split[0], if (split.size > 1) split.slice(1 until split.size).joinToString(separator = " ") else "")
}

fun badCommand(parsed: Pair<String, String>) {
    println("No such command: ${parsed.first}")
}

fun main(args: Array<String>) {
    val users = UserManager()


    do {
        val line = readLine() ?: ""
        var parsed = parse(line)


        when (parsed.first.toLowerCase()) {
            "create" -> {
                parsed = parse(parsed)
                when (parsed.first) {
                    "goal" -> println("New goal created")
                    else -> println("Cannot create ${parsed.first}")
                }
            }

            // Users
            "user" -> {
                parsed = parse(parsed)
                when (parsed.first) {
                    "list", "display" -> {
                        val list = users.list()
                        for (user in list) {

                            println("$user: ${if (user.authorized) "authorized" else "unauthorized"}")
                        }

                        if (list.isEmpty()) {
                            println("No users were registered yet.")
                        }
                    }
                    "login", "authorize" -> {
                        parsed = parse(parsed)
                        val user = users[parsed.first]
                        if (user != null) {
                            if (user.authorized) println("User '${parsed.first}' has already logged in.")
                            user.authorized = true
                            println("User '${parsed.first}' has logged in.")
                        } else
                            println("User '${parsed.first}' was not registered yet.")
                    }
                    "logout" -> {
                        parsed = parse(parsed)

                        val user = users[parsed.first]
                        if (user != null) {
                            if (!user.authorized) println("User '${parsed.first}' is not logged in.")
                            user.authorized = false
                            println("User '${parsed.first}' has logged out.")
                        } else
                            println("User '${parsed.first}' was not registered yet.")
                    }
                    "register" -> {
                        if (users[parsed.second] != null) {
                            println("Username '${parsed.second}' is already taken.")
                        } else {
                            users.register(parsed.second)
                            println("User '${parsed.second}' has registered.")
                        }
                    }
                    "delete" -> {
                        // delete user
                        parsed = parse(parsed)

                        if (users[parsed.first] == null) {
                            println("User '${parsed.first}' was not registered yet.")
                        } else {
                            users.delete(parsed.first)
                            println("User '${parsed.first}' was deleted.")
                        }

                    }
                    else -> badCommand(parsed)
                }
            }

            // Exit
            "exit" -> return
            else -> badCommand(parsed)
        }
    } while (true)
}

