local M = {}

function M.exit()
	sys.exit(0)
	if html5 then html5.run("window.close()") end
end

return M