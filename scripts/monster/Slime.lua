function Interact(monster)
    local state = monster:GetState()
    if(state == ObjectState.IDLE) then
        --Calculate distances
        local mx,my = monster:GetCenter()
        local px,py = GetPlayerCenter()
        local dist = GetDistance(mx,my,px,py)
        if(dist > 8) then
            monster:SetState(ObjectState.MOVE)
        end
        print(dist)
    end
end
