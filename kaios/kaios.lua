local info = sys.get_sys_info()

if not info.user_agent:find("KAIOS") then
	kaios = nil
	return
end

function kaios.exit()
	sys.exit(0)
	if html5 then html5.run("window.close()") end
end


function kaios.play_sound(file)
	if html5 then html5.run("kaios_playAudioFromURL('" .. sys.get_application_path() .. "/" .. file .. "');") end
end

return kaios