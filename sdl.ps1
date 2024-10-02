function Clone-RepoIfNotExists {
    param (
        [string]$gitUrl,
        [string]$targetDir
    )

    # Clone the Git repository if it doesn't exist
    if (-not (Test-Path -Path $targetDir)) {
        Write-Host "Cloning repository from $gitUrl $targetDir"
        try {
            # Use Start-Process to clone the repo and wait for it to finish
            Start-Process -FilePath git -ArgumentList "clone", $gitUrl, $targetDir -Wait -ErrorAction Stop
            Write-Host "Cloned repository successfully."
        } catch {
            Write-Host "Error occurred while cloning the repository: $_"
            return
        }
    } else {
        Write-Host "Repository already exists at $targetDir."
    }

    # Create build directories if they don't exist
    $buildDebugPath = Join-Path $targetDir "build/debug"
    $buildReleasePath = Join-Path $targetDir "build/release"

    if (-not (Test-Path -Path $buildDebugPath)) {
        Write-Host "Creating Debug build directory at $buildDebugPath..."
        New-Item -Path $buildDebugPath -ItemType Directory | Out-Null
    }
    if (-not (Test-Path -Path $buildReleasePath)) {
        Write-Host "Creating Release build directory at $buildReleasePath..."
        New-Item -Path $buildReleasePath -ItemType Directory | Out-Null
    }
}
function Move-BuiltFiles {
    param (
        [string]$sourcePath,
        [string]$destinationPath
    )

    # Search for .lib, .a, and .dll files and move them to the destination
    $files = Get-ChildItem -Path $sourcePath -Recurse -Include *.lib, *.a, *.dll
    if ($files) {
        foreach ($file in $files) {
            Move-Item -Path $file.FullName -Destination $destinationPath -Force
        }
        Write-Host "Moved build files to $destinationPath"
    } else {
        Write-Host "No build files found to move."
    }
}


# Set paths based on script's location
$root = $PSScriptRoot
$libPath = Join-Path $root "lib"
$libDebugPath = Join-Path $libPath "debug"
$libReleasePath = Join-Path $libPath "release"
$vendorPath = Join-Path $root "vendor"
$sdlPath = Join-Path $vendorPath "SDL3"
$imagePath = Join-Path $vendorPath "SDL3_Image"
$ttfPath = Join-Path $vendorPath "STD_TTF"

$buildSDLDebugPath = Join-Path $sdlPath "build/debug"
$buildSDLReleasePath = Join-Path $sdlPath "build/release"

$buildImageDebugPath = Join-Path $imagePath "build/debug"
$buildImageReleasePath = Join-Path $imagePath "build/release"

# Create lib/debug and lib/release directories
if (-not (Test-Path -Path $libPath)) {
    Write-Host "Creating lib structure..."
    New-Item -Path $libPath -ItemType Directory | Out-Null
}
if (-not (Test-Path -Path $libDebugPath)) {
    New-Item -Path $libDebugPath -ItemType Directory | Out-Null
}
if (-not (Test-Path -Path $libReleasePath)) {
    New-Item -Path $libReleasePath -ItemType Directory | Out-Null
}

# Create vendor directory
if (-not (Test-Path -Path $vendorPath)) {
    Write-Host "Creating vendor directory..."
    New-Item -Path $vendorPath -ItemType Directory | Out-Null
}

Clone-RepoIfNotExists -gitUrl "https://github.com/libsdl-org/SDL.git" -targetDir $sdlPath
Clone-RepoIfNotExists -gitUrl "https://github.com/libsdl-org/SDL_image.git" -targetDir $imagePath
Clone-RepoIfNotExists -gitUrl "https://github.com/libsdl-org/SDL_ttf.git" -targetDir $ttfPath

<#
# Build Debug configuration
Write-Host "Building Debug configuration..."
Set-Location $buildSDLDebugPath
Invoke-Expression 'cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../..'
if (Invoke-Expression 'cmake --build . --config Debug') {
    Write-Host "Debug build successful."
    Move-BuiltFiles -sourcePath $buildSDLDebugPath -destinationPath $libDebugPath
} else {
    Write-Host "Debug build failed."
    exit 1
}

# Build Release configuration
Write-Host "Building Release configuration..."
Set-Location $buildSDLReleasePath
Invoke-Expression 'cmake -G Ninja -DCMAKE_BUILD_TYPE=Release ../..'
if (Invoke-Expression 'cmake --build . --config Release') {
    Write-Host "Release build successful."
    Move-BuiltFiles -sourcePath $buildSDLReleasePath -destinationPath $libReleasePath
} else {
    Write-Host "Release build failed."
    exit 1
}

# Build Debug configuration
Write-Host "Building Debug configuration..."
Set-Location # Build Debug configuration

Write-Host "Building Debug configuration..."
Set-Location $buildImageDebugPath
Invoke-Expression 'cmake -G Ninja -DCMAKE_BUILD_TYPE=Debug ../..'
if (Invoke-Expression 'cmake --build . --config Debug') {
    Write-Host "Debug build successful."
    Move-BuiltFiles -sourcePath $buildImageDebugPath -destinationPath $libDebugPath
} else {
    Write-Host "Debug build failed."
    exit 1
}
#>

Write-Host "Building Release configuration..."
Set-Location $buildImageReleasePath
Invoke-Expression 'cmake -DSDL3_DIR=$sdlPath -DCMAKE_BUILD_TYPE=Release ../..'
if (Invoke-Expression 'cmake --build . --config Release') {
    Write-Host "Release build successful."
    Move-BuiltFiles -sourcePath $buildImageReleasePath -destinationPath $libReleasePath
} else {
    Write-Host "Release build failed."
    exit 1
}


#git clone https://github.com/libsdl-org/SDL_image.git vendor/SDL_image
#git clone https://github.com/libsdl-org/SDL_ttf.git vendor/SDL_ttf
