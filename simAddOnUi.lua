function sysCall_info()
	return {autoStart=true}
end

function sysCall_addOnScriptSuspend()
    return {cmd='cleanup'}
end

function sysCall_init()
	x = 0

xml = [[
<ui closable="true" resizable="false" activate="true" enable="true"
    title="MainWindow" align="center" size="150,50">
    <group layout="vbox">
    <group layout="grid">
        <button text="Charger" on-click="buttonClick1"  id="1"/>
        <button text="Demarrer" on-click="buttonClick2"  id="2"/>
        <button text="Arreter" on-click="buttonClick3" id="3"/>
    </group> 
    <group>
    <label text="Position" id="4" />
    </group>
    <group layout="grid">
        <text-browser text="0.0" id="5"/>
         <text-browser text="0.0" id="6"/>
         <text-browser text="0.0" id="7"/>
         <text-browser text="0.0" id="8"/>
         <text-browser text="0.0" id="9"/>
         <text-browser text="0.0" id="10"/>
    </group>
    </group>
</ui>
]]

ui=simUI.create(xml)


end

function buttonClick1()
	sim.loadScene("./scenes/ProjetSimulateur.ttt".."@keepCurrent")
end

function buttonClick2(Joint1)
	
	if (x == 0) then
 		sim.startSimulation()
		x = x + 1
	else
		sim.pauseSimulation()
		x = x -1
	end
	
end


function buttonClick3()
	sim.stopSimulation()
end

function joint1(ui,id,Pos1)

	Joint1 = sim.getObject('/UR5/joint1')
	Pos1 = sim.getJointPosition(Joint1)
	simUI.setText(ui,5,string.format(Pos1))
end

function joint2(ui,id,Pos2)
	Joint2 = sim.getObject('/UR5/joint2',-1,-1,0)
	Pos2 = sim.getJointPosition(Joint2)
	simUI.setText(ui,6,string.format(Pos2))
	return (SPos2)
end

function joint3(ui,id,Pos3)
	Joint3 = sim.getObject('/UR5/joint3',-1,-1,0)
	Pos3 = sim.getJointPosition(Joint3)
	simUI.setText(ui,7,string.format(Pos3))
end

function joint4(ui,id,Pos4)
	Joint4 = sim.getObject('/UR5/joint4',-1,-1,0)
	Pos4 = sim.getJointPosition(Joint4)
	simUI.setText(ui,8,string.format(Pos4))
end

function joint5(ui,id,Pos5)
	Joint5 = sim.getObject('/UR5/joint5',-1,-1,0)
	Pos5 = sim.getJointPosition(Joint5)
	simUI.setText(ui,9,string.format(Pos5))
end

function joint6(ui,id,Pos6)
	Joint6 = sim.getObject('/UR5/joint6',-1,-1,0)
	Pos6 = sim.getJointPosition(Joint6)
	simUI.setText(ui,10,string.format(Pos6))
end

function onCloseClicked()
    leaveNow=true
end