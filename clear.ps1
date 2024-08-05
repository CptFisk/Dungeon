# Define an array of folder paths
$folderPaths = @(
    "out\debug\rsrc",
    "out\release\rsrc",
    "out\editor\debug\rsrc",
    "out\editor\release\rsrc"
)

# Iterate over each folder path in the array
foreach ($folderPath in $folderPaths) {
    # Check if the folder exists
    if (Test-Path $folderPath) {
        try {
            # Remove the folder and its contents
            Remove-Item -Path $folderPath -Recurse -Force
            Write-Output "The folder '$folderPath' and its contents have been successfully removed."
        } catch {
            Write-Error "An error occurred while trying to remove the folder '$folderPath': $_"
        }
    } else {
        Write-Output "The specified folder '$folderPath' does not exist."
    }
}
