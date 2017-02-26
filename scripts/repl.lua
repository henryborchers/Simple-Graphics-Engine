--
-- Created by IntelliJ IDEA.
-- User: hborcher
-- Date: 2/11/17
-- Time: 11:33 PM
-- To change this template use File | Settings | File Templates.
--

local engine = require "libgengine"

local types = { "pane" }

function types.isValid(t)
    for k, v in pairs(types) do
        if v == t then
            return true
        end
    end
    return false
end

objects = {}

function objects:isValid(id)
    for k, v in pairs(self) do
        if k == id then
            return true
        end
    end
    return false
end

commands = {}

-- FIXME: why does this need a dummy variable
function commands.delete(scope, id)
    local index = tonumber(id)
    if objects:isValid(index) then
        print("Deleting " .. index)
        objects[index]:remove()
        table.remove(objects, index)

    else
        print("Invalid Id")
    end

end

function commands.create(parent, t, ...)
    assert(types.isValid(t))
--    print(parent)
    local args = { ... }

    local x = tonumber(args[1])
    local y = tonumber(args[2])
    local height = tonumber(args[3])
    local width = tonumber(args[4])
    print("Creating a " .. t .. " at " .. x .. "x" .. y .. " that is " .. height .. " pixels by " .. width .. " pixels.")
    local cmd_creater = parent .. ":create_" .. t .. "(" .. width .. ", " .. height .. ")"
    print(cmd_creater)
    local cmd = assert(load("return " .. cmd_creater))

    local new_item = cmd()
    new_item:setOrientation(x, y)
    objects[#objects + 1] = new_item
end

function build_function(object, cmd, args)
    print("object = " .. object)
    print("cmd = " .. cmd)

    --    local func = cmd .. "(".. object .. ", \""
    --    func = "commands." .. func .. table.concat(args, "\", \"") .. "\")"
    --
    local func = "commands." .. cmd .. "(\"" .. object .. "\", \"" .. table.concat(args, "\", \"") .. "\")"
    print("function build = " .. func)
    return assert(load("return " .. func))
end

local function list_objects(objects)
    for k, v in pairs(objects) do
        print(k, v)
    end
end

local function parse_command(text)
    local cmd
    local args = {}
    local count = 0

    for word in text:gmatch("%w+") do
        if count == 0 then
            cmd = word
        else
            args[#args + 1] = word
        end
        count = count + 1
    end

    return cmd, args
end


print("running REPL")
window = engine.window.new(640, 480, "graphics")

while true do
    window:mainloop()
    print("enter a command")
    local text_input = io.read()

    if text_input == 'quit' then break end
    if text_input == 'list' then
        list_objects(objects)
    else


        local command_name, command_args = parse_command(text_input)
        print("command name is " .. command_name)
        if commands[command_name] == nil then
            print("Not in commands")
        else
            local status, err, func

            status, err = pcall(function() func = build_function("window", command_name, command_args) end)
            if not status then
                print("Unable to build function command")
            else

                status, err = pcall(func)
                if not status then
                    print("Error running command. Reason: " .. err)
                end
            end
        end


    end

end

print("all done")
