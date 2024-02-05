function Update-FileContent {
    param (
        [Parameter(Mandatory=$true)]
        [string]$FilePath
    )

    # Check if file exists
    if (-not (Test-Path $FilePath)) {
        Write-Error "File does not exist."
        return
    }

    # Read file content
    $content = Get-Content $FilePath -Raw

    # Initialize a stack to track "_v<" nesting
    $stack = New-Object System.Collections.Generic.Stack[string]

    # Initialize a StringBuilder for better performance
    $result = New-Object System.Text.StringBuilder

    # Iterate over each character
    for ($i = 0; $i -lt $content.Length; $i++) {
        switch ($content[$i]) {
            '_' {
                if ($content.Substring($i, 3) -eq '_v<') {
                    # Found "_v<", push to stack
                    $stack.Push("_v")
                    [void]$result.Append('<')
                    $i += 2 # Skip "v<"
                } else {
                    [void]$result.Append($content[$i])
                }
            }
            '<' {
                    $stack.Push("<")
                [void]$result.Append($content[$i])
            }
            '>' {
                if ($stack.Count -gt 0) {
                    # Found ">", pop from stack
                    $top = $stack.Pop()
                    [void]$result.Append('>')
                    if ($top -eq "_v") {
                        # Append "::value" if top was "_v"
                        [void]$result.Append('::value')
                    }
                } else {
                    [void]$result.Append('>')
                }
            }
            default {
                [void]$result.Append($content[$i])
            }
        }
    }

    # Generate new file path
    $directory = [System.IO.Path]::GetDirectoryName($FilePath)
    $fileName = [System.IO.Path]::GetFileNameWithoutExtension($FilePath)
    $extension = [System.IO.Path]::GetExtension($FilePath)
    $newFilePath = Join-Path $directory ($fileName + "_s" + $extension)

    # Save result to new file
    $result.ToString() | Out-File $newFilePath -Encoding UTF8

    Write-Host "File processed and saved as $newFilePath"
}

# To use the function: Update-FileContent -FilePath "C:\path\to\your\file.cpp"