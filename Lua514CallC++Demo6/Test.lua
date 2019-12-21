print "Hello, Lua Demo5!"

name="my name is lua"

iVar = 5

nameTable={sex = "male", age=18}

function PrintLuaLog()
	print("name: " ..name)
	print("iVar: " ..iVar)

	for key, value in pairs(nameTable) do
		print("key: "..key .. "  value: ".. value)
	end
end

function AddIncrease()
	iVar = iVar + 10
	nameTable.age = nameTable.age + 10

end


PrintLuaLog()

